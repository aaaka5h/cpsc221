/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal. 
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    // TODO
    // 1. Label all edges and vertices as unexplored. You will need 
    //    to look in graph.h for the right functions.
    vector<Vertex> vertices = graph.getVertices();
    size_t V = (size_t) vertices.size();
    for (size_t i=0; i<V; i++) {
        graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }

    vector<Edge> edges = graph.getEdges();
    size_t E = (size_t) edges.size();
    for (size_t i=0; i<E; i++) {
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }

    // 2. Use the BFS function in graph_tools to find the minimum edge. 
    //    Don't forget to label it.
    Vertex start = graph.getStartingVertex();
    Edge minWeight = BFS(graph, start);
    graph.setEdgeLabel(minWeight.source, minWeight.dest, "MIN");
    return minWeight.weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end) {
    unordered_map<Vertex, Vertex> parent;
    
    // TODO
    // 1. Set all verticesas unexplored
    vector<Vertex> vertices = graph.getVertices();
    int V = (int) vertices.size();
    for (int i=0; i<V; i++) {
        graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }

    vector<Edge> edges = graph.getEdges();
    int E = (int) edges.size();
    for (int i=0; i<E; i++) {
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }

    // 2. Do a modified BFS. See the BFS function below as a guideline, but 
    //    your BFS here only needs to populate the "parent" map and stop once the short-
    //    est path has been found.
    bool STOP;
    queue<Vertex> queue;
    graph.setVertexLabel(start, "VISITED");
    queue.push(start);
    STOP = false;

    while (!queue.empty() && !STOP) {
        Vertex vertex = queue.front();
        graph.setVertexLabel(vertex, "VISITED");
        vector<Vertex> adjacents = graph.getAdjacent(vertex);
        int A = (int) adjacents.size();

        for (int i=0; i<A; i++) {
            if (graph.getVertexLabel(adjacents[i])== "UNEXPLORED") {
                graph.setVertexLabel(adjacents[i], "VISITED");
                queue.push(adjacents[i]);
                parent[adjacents[i]] = vertex;
            }
            if (adjacents[i] == end) {
                STOP = true;
                break;
            }
        }

        if (!STOP) queue.pop();
    }

    // 3. Use the unordered map to trace from a path from the end to the start, 
    //    counting edges. You should set edges to "minpath" here too.
    int minPath = -1;

    if (STOP) {
        minPath = (int) 0;
        Vertex currVertex = end;
        
        while (currVertex != start) {
            graph.setEdgeLabel(currVertex, parent[currVertex], "MINPATH");
            currVertex = parent[currVertex];
            minPath++;
        }
    }
    
    return minPath;
}

/**
 * BONUS: Finds a minimal spanning tree on a graph.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class given in dsets.cpp to help you with
 *  Kruskal's algorithm.
 *
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    // TODO
}

/**
 * Does a BFS of a graph, keeping track of the minimum
 *  weight edge seen so far.
 * @param g - the graph
 * @param start - the vertex to start the BFS from
 * @return the minimum weight edge
 */
Edge GraphTools::BFS(Graph& graph, Vertex start)
{
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Edge min;
    min.weight = INT_MAX;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            } else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "CROSS");
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            }
        }
    }
    return min;
}
