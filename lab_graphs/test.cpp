#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "graph.h"
#include "premade_graphs.cpp"
#include "graph_tools.h"

using namespace std;

/*
void temp() {
    Graph* graph = new Graph(PremadeGraphs::createUSMap(weighted));
    graph = new Graph(PremadeGraphs::createEuropeMap(weighted));
    graph = new Graph(PremadeGraphs::createJapanMap(weighted));
    graph = new Graph(weighted, numVertices, seed);
    
    for (auto e : graph.getEdges()) {
        if (e.weight == ans) {
            cout << e.source << " " << e.dest << endl;
        }
    }
} */

TEST_CASE("minWeight::US","[weight=0][part=minWeight]"){
	Graph graph(PremadeGraphs::createUSMap(true));
    int ans = GraphTools::findMinWeight(graph);
    graph.savePNG("min-weight-US");
    REQUIRE(ans == 126);
    REQUIRE(graph.getEdgeLabel(2, 1) == "MIN");
    int count = 0;
    for (auto e : graph.getEdges()) {
        if (e.label == "MIN") {
            count++;
        }
    }
    REQUIRE(count == 1);
}

TEST_CASE("minWeight::Europe","[weight=0][part=minWeight]"){
	Graph graph(PremadeGraphs::createEuropeMap(true));
    int ans = GraphTools::findMinWeight(graph);
    graph.savePNG("min-weight-Europe");
    REQUIRE(ans == 174);
    REQUIRE(graph.getEdgeLabel(7, 1) == "MIN");
    int count = 0;
    for (auto e : graph.getEdges()) {
        if (e.label == "MIN") {
            count++;
        }
    }
    REQUIRE(count == 1);
}

TEST_CASE("minWeight::Japan","[weight=0][part=minWeight]"){
	Graph graph(PremadeGraphs::createJapanMap(true));
    int ans = GraphTools::findMinWeight(graph);
    graph.savePNG("min-weight-Japan");
    REQUIRE(ans == 15);
    REQUIRE(graph.getEdgeLabel(8, 6) == "MIN");
    int count = 0;
    for (auto e : graph.getEdges()) {
        if (e.label == "MIN") {
            count++;
        }
    }
    REQUIRE(count == 1);
}

TEST_CASE("minPath::US","[weight=0][part=minPath]"){
	Graph graph(PremadeGraphs::createUSMap(false));
    Vertex s = PremadeGraphs::getStartVertex("us");
    Vertex e = PremadeGraphs::getEndVertex("us");
    int ans = GraphTools::findShortestPath(graph, s, e);
    graph.savePNG("shortest-path-US");
    REQUIRE(ans == 3);
    // Validate path
    int count = 0;
    int checkXor = s ^ e;
    for (auto e : graph.getEdges()) {
        if (e.label == "MINPATH") {
            count++;
            checkXor ^= (e.source ^ e.dest);
        }
    }
    REQUIRE(count == ans);
    REQUIRE(checkXor == 0);
}

TEST_CASE("minPath::Europe","[weight=0][part=minPath]"){
	Graph graph(PremadeGraphs::createEuropeMap(false));
    Vertex s = PremadeGraphs::getStartVertex("europe");
    Vertex e = PremadeGraphs::getEndVertex("europe");
    int ans = GraphTools::findShortestPath(graph, s, e);
    graph.savePNG("shortest-path-Europe");
    REQUIRE(ans == 2);
    // Validate path
    int count = 0;
    int checkXor = s ^ e;
    for (auto e : graph.getEdges()) {
        if (e.label == "MINPATH") {
            count++;
            checkXor ^= (e.source ^ e.dest);
        }
    }
    REQUIRE(count == ans);
    REQUIRE(checkXor == 0);
}

TEST_CASE("minPath::Japan","[weight=0][part=minPath]"){
	Graph graph(PremadeGraphs::createJapanMap(false));
    Vertex s = PremadeGraphs::getStartVertex("japan");
    Vertex e = PremadeGraphs::getEndVertex("japan");
    int ans = GraphTools::findShortestPath(graph, s, e);
    graph.savePNG("shortest-path-Japan");
    REQUIRE(ans == 2);
    // Validate path
    int count = 0;
    int checkXor = s ^ e;
    for (auto e : graph.getEdges()) {
        if (e.label == "MINPATH") {
            count++;
            checkXor ^= (e.source ^ e.dest);
        }
    }
    REQUIRE(count == ans);
    REQUIRE(checkXor == 0);
}

TEST_CASE("mst::US","[weight=0][part=mst]"){
	Graph graph(PremadeGraphs::createUSMap(true));
    GraphTools::findMST(graph);
    graph.savePNG("mst-US");
    int count = 0;
    int weight = 0;
    int n = graph.getVertices().size();
    vector<bool> check(n, false);
    for (auto e : graph.getEdges()) {
        if (e.label == "MST") {
            count++;
            weight += e.weight;
            check[e.source] = check[e.dest] = true;
        }
    }
    bool isTree = true;
    for (auto b : check) {
        if (!b) {
            isTree = false;
            break;
        }
    }
    REQUIRE(count == n-1);
    REQUIRE(isTree);
    REQUIRE(weight == 1481);
}

TEST_CASE("mst::Europe","[weight=0][part=mst]"){
	Graph graph(PremadeGraphs::createEuropeMap(true));
    GraphTools::findMST(graph);
    graph.savePNG("mst-Europe");
    int count = 0;
    int weight = 0;
    int n = graph.getVertices().size();
    vector<bool> check(n, false);
    for (auto e : graph.getEdges()) {
        if (e.label == "MST") {
            count++;
            weight += e.weight;
            check[e.source] = check[e.dest] = true;
        }
    }
    bool isTree = true;
    for (auto b : check) {
        if (!b) {
            isTree = false;
            break;
        }
    }
    REQUIRE(count == n-1);
    REQUIRE(isTree);
    REQUIRE(weight == 3019);
}

TEST_CASE("mst::Japan","[weight=0][part=mst]"){
	Graph graph(PremadeGraphs::createJapanMap(true));
    GraphTools::findMST(graph);
    graph.savePNG("mst-Japan");
    int count = 0;
    int weight = 0;
    int n = graph.getVertices().size();
    vector<bool> check(n, false);
    for (auto e : graph.getEdges()) {
        if (e.label == "MST") {
            count++;
            weight += e.weight;
            check[e.source] = check[e.dest] = true;
        }
    }
    bool isTree = true;
    for (auto b : check) {
        if (!b) {
            isTree = false;
            break;
        }
    }
    REQUIRE(count == n-1);
    REQUIRE(isTree);
    REQUIRE(weight == 400);
}