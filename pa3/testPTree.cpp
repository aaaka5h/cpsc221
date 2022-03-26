/*
*  File:        testPTree.cpp
*  Description: Basic test cases for PTree class, CPSC 221 2021W2 PA3
*               
*               Recommended for you to modify and/or add test cases!
* 
*  Date:        2022-03-03 02:46
*/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "cs221util/catch.hpp"

#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"

#include "ptree.h"
#include "hue_utils.h"

using namespace cs221util;
using namespace std;

TEST_CASE("PTree::Constructor", "[weight=1][part=ptree]") {
  //cout << "Testing PTree constructor..." << endl;
  
  // local variables for testing
  vector<double> components;
  double avgx, avgy, avgh, avgs, avgl;
  double sum = 0;
  Node* nd;

  // manually create a PNG, 3x2
  PNG source;
  source.resize(3, 2);
  HSLAPixel* px00 = source.getPixel(0, 0);
  HSLAPixel* px01 = source.getPixel(0, 1);
  HSLAPixel* px10 = source.getPixel(1, 0);
  HSLAPixel* px11 = source.getPixel(1, 1);
  HSLAPixel* px20 = source.getPixel(2, 0);
  HSLAPixel* px21 = source.getPixel(2, 1);

  *px00 = HSLAPixel(  0, 0.2, 0.4);    *px10 = HSLAPixel( 40, 0.3, 0.5);     *px20 = HSLAPixel( 60, 0.2, 0.6);
  *px01 = HSLAPixel(350, 0.8, 0.2);    *px11 = HSLAPixel(240, 0.1, 0.8);     *px21 = HSLAPixel(320, 0.7, 0.4);

  // call the tree constructor
  PTree tree(source);

  // check the node contents
  Node* nd_root = tree.GetRoot();

  // root node
  nd = nd_root;
  REQUIRE(nd->upperleft == make_pair((unsigned int)0, (unsigned int)0));
  REQUIRE(nd->width == 3);
  REQUIRE(nd->height == 2);
  // get the average colour
  sum = 0;  components.clear();
  components.push_back(Deg2X(px00->h));  components.push_back(Deg2X(px10->h));  components.push_back(Deg2X(px20->h));
  components.push_back(Deg2X(px01->h));  components.push_back(Deg2X(px11->h));  components.push_back(Deg2X(px21->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgx = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(Deg2Y(px00->h));  components.push_back(Deg2Y(px10->h));  components.push_back(Deg2Y(px20->h));
  components.push_back(Deg2Y(px01->h));  components.push_back(Deg2Y(px11->h));  components.push_back(Deg2Y(px21->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgy = sum / components.size();
  avgh = XY2Deg(avgx, avgy);
  sum = 0;  components.clear();
  components.push_back(px00->s);  components.push_back(px10->s);  components.push_back(px20->s);
  components.push_back(px01->s);  components.push_back(px11->s);  components.push_back(px21->s);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgs = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(px00->l);  components.push_back(px10->l);  components.push_back(px20->l);
  components.push_back(px01->l);  components.push_back(px11->l);  components.push_back(px21->l);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgl = sum / components.size();

  REQUIRE(nd->avg == HSLAPixel(avgh, avgs, avgl));

  // root->A
  nd = nd_root->A;
  REQUIRE(nd->upperleft == make_pair((unsigned int)0, (unsigned int)0));
  REQUIRE(nd->width == 1);
  REQUIRE(nd->height == 2);
  // get the average colour
  sum = 0;  components.clear();
  components.push_back(Deg2X(px00->h));
  components.push_back(Deg2X(px01->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgx = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(Deg2Y(px00->h));
  components.push_back(Deg2Y(px01->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgy = sum / components.size();
  avgh = XY2Deg(avgx, avgy);
  sum = 0;  components.clear();
  components.push_back(px00->s);
  components.push_back(px01->s);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgs = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(px00->l);
  components.push_back(px01->l);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgl = sum / components.size();

  REQUIRE(nd->avg == HSLAPixel(avgh, avgs, avgl));

  // root->B
  nd = nd_root->B;
  REQUIRE(nd->upperleft == make_pair((unsigned int)1, (unsigned int)0));
  REQUIRE(nd->width == 2);
  REQUIRE(nd->height == 2);
  // get the average colour
  sum = 0;  components.clear();
  components.push_back(Deg2X(px10->h));  components.push_back(Deg2X(px20->h));
  components.push_back(Deg2X(px11->h));  components.push_back(Deg2X(px21->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgx = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(Deg2Y(px10->h));  components.push_back(Deg2Y(px20->h));
  components.push_back(Deg2Y(px11->h));  components.push_back(Deg2Y(px21->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgy = sum / components.size();
  avgh = XY2Deg(avgx, avgy);
  sum = 0;  components.clear();
  components.push_back(px10->s);  components.push_back(px20->s);
  components.push_back(px11->s);  components.push_back(px21->s);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgs = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(px10->l);  components.push_back(px20->l);
  components.push_back(px11->l);  components.push_back(px21->l);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgl = sum / components.size();

  REQUIRE(nd->avg == HSLAPixel(avgh, avgs, avgl));

  //root->B->A->B
  nd = nd_root->B->A->B;
  REQUIRE(nd->upperleft == make_pair((unsigned int)1, (unsigned int)1));
  REQUIRE(nd->width == 1);
  REQUIRE(nd->height == 1);
  // get the average colour
  sum = 0;  components.clear();
  components.push_back(Deg2X(px11->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgx = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(Deg2Y(px11->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgy = sum / components.size();
  avgh = XY2Deg(avgx, avgy);
  sum = 0;  components.clear();
  components.push_back(px11->s);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgs = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(px11->l);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgl = sum / components.size();

  REQUIRE(nd->avg == HSLAPixel(avgh, avgs, avgl));

  // root->B->B->A
  nd = nd_root->B->B->A;
  REQUIRE(nd->upperleft == make_pair((unsigned int)2, (unsigned int)0));
  REQUIRE(nd->width == 1);
  REQUIRE(nd->height == 1);
  // get the average colour
  sum = 0;  components.clear();
  components.push_back(Deg2X(px20->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgx = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(Deg2Y(px20->h));
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgy = sum / components.size();
  avgh = XY2Deg(avgx, avgy);
  sum = 0;  components.clear();
  components.push_back(px20->s);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgs = sum / components.size();
  sum = 0;  components.clear();
  components.push_back(px20->l);
  for (unsigned int i = 0; i < components.size(); i++)
    sum += components[i];
  avgl = sum / components.size();

  REQUIRE(nd->avg == HSLAPixel(avgh, avgs, avgl));
}

TEST_CASE("PTree::Size_NumLeaves", "[weight=1][part=ptree]") {
  //cout << "Testing PTree Size, NumLeaves..." << endl;

  // manually create a PNG, 3x2
  PNG source;
  source.resize(3, 2);
  HSLAPixel* px00 = source.getPixel(0, 0);
  HSLAPixel* px01 = source.getPixel(0, 1);
  HSLAPixel* px10 = source.getPixel(1, 0);
  HSLAPixel* px11 = source.getPixel(1, 1);
  HSLAPixel* px20 = source.getPixel(2, 0);
  HSLAPixel* px21 = source.getPixel(2, 1);

  *px00 = HSLAPixel(0, 0.2, 0.4);    *px10 = HSLAPixel(40, 0.3, 0.5);     *px20 = HSLAPixel(60, 0.2, 0.6);
  *px01 = HSLAPixel(350, 0.8, 0.2);    *px11 = HSLAPixel(240, 0.1, 0.8);     *px21 = HSLAPixel(320, 0.7, 0.4);

  // call the tree constructor
  PTree tree(source);

  int treesize = tree.Size();
  int treenumleaves = tree.NumLeaves();

  REQUIRE(treesize == 11);
  REQUIRE(treenumleaves == 6);
}

TEST_CASE("PTree::CopyConstructor_operator=", "[weight=1][part=ptree]") {
  //cout << "Testing PTree CopyConstructor_operator=..." << endl;

  PNG source1;
  source1.readFromFile("originals/mix-3x5.png");

  PNG source2;
  source2.readFromFile("originals/pruneto9leaves-5x3.png");

  PTree tree1(source1);

  PTree tree2(tree1);

  Node* t1root = tree1.GetRoot();
  Node* t1rA = t1root->A;
  Node* t1rB = t1root->B;
  Node* t1rBBAA = t1root->B->B->A->A;

  Node* t2root = tree2.GetRoot();
  Node* t2rA = t2root->A;
  Node* t2rB = t2root->B;
  Node* t2rBBAA = t2root->B->B->A->A;

  REQUIRE(t1root != t2root);
  REQUIRE(t1rA != t2rA);
  REQUIRE(t1rB != t2rB);
  REQUIRE(t1rBBAA != t2rBBAA);

  REQUIRE(t1rBBAA->avg == t2rBBAA->avg);

  PTree tree3(source2);

  tree2 = tree3;

  Node* t3root = tree3.GetRoot();
  Node* t3rA = t3root->A;
  Node* t3rB = t3root->B;
  Node* t3rBBAA = t3root->B->B->A->A;

  Node* t2newroot = tree2.GetRoot();
  t2rA = t2newroot->A;
  t2rB = t2newroot->B;
  t2rBBAA = t2newroot->B->B->A->A;

  REQUIRE(t2newroot != t2root);

  REQUIRE(t3root != t2newroot);
  REQUIRE(t3rA != t2rA);
  REQUIRE(t3rB != t2rB);
  REQUIRE(t3rBBAA != t2rBBAA);

  REQUIRE(t3rBBAA->avg == t2rBBAA->avg);
  
}

TEST_CASE("PTree::Render", "[weight=1][part=ptree]") {
  //cout << "Testing PTree Render..." << endl;

  PNG source;
  source.readFromFile("originals/kkkk-256x224.png");

  // call the tree constructor
  PTree tree(source);

  PNG output = tree.Render();

  output.writeToFile("images/render-kkkk.png");

  REQUIRE(output == source);
}

TEST_CASE("PTree::Prune_small", "[weight=1][part=ptree]") {
  //cout << "Testing PTree Prune_small..." << endl;

  PNG source;
  source.readFromFile("originals/pruneto9leaves-5x3.png");

  // call the tree constructor
  PTree tree(source);

  int treesize = tree.Size();
  int treenumleaves = tree.NumLeaves();

  REQUIRE(treesize == 29);
  REQUIRE(treenumleaves == 15);

  // pruning tree
  tree.Prune(0.02);
  treesize = tree.Size();
  treenumleaves = tree.NumLeaves();

  REQUIRE(treesize == 17);
  REQUIRE(treenumleaves == 9);
}

TEST_CASE("PTree::Prune_large_render", "[weight=1][part=ptree]") {
  //cout << "Testing PTree Prune_large..." << endl;

  PNG source;
  source.readFromFile("originals/kkkk-256x224.png");

  // call the tree constructor
  PTree tree(source);

  // pruning tree
  tree.Prune(0.05);
  int treesize = tree.Size();
  int treenumleaves = tree.NumLeaves();

  PNG soln_image;
  soln_image.readFromFile("soln-images/soln-prune-kkkk-tol005.png");

  PNG output = tree.Render();

  output.writeToFile("images/prune-kkkk-tol005.png");

  REQUIRE(treesize == 13035);
  REQUIRE(treenumleaves == 6518);

  REQUIRE(output == soln_image);
}

TEST_CASE("PTree::FlipHorizontal_small", "[weight=1][part=ptree]") {
  //cout << "Testing PTree FlipHorizontal_small..." << endl;

  PNG source;
  source.readFromFile("originals/mix-5x3.png");

  // call the tree constructor
  PTree tree(source);

  // FlipHorizontal tree
  tree.FlipHorizontal();

  PNG soln_image;
  soln_image.readFromFile("soln-images/soln-fliphorizontal-mix-5x3.png");

  PNG output = tree.Render();

  output.writeToFile("images/fliphorizontal-mix-5x3.png");

  REQUIRE(output == soln_image);
}

TEST_CASE("PTree::FlipHorizontal_large", "[weight=1][part=ptree]") {
  //cout << "Testing PTree FlipHorizontal_large..." << endl;

  PNG source;
  source.readFromFile("originals/cs-256x224.png");

  // call the tree constructor
  PTree tree(source);

  // FlipHorizontal tree
  tree.FlipHorizontal();

  PNG soln_image;
  soln_image.readFromFile("soln-images/soln-fliphorizontal-cs.png");

  PNG output = tree.Render();

  output.writeToFile("images/fliphorizontal-cs.png");

  REQUIRE(output == soln_image);
}

TEST_CASE("PTree::FlipVertical_small", "[weight=1][part=ptree]") {
  //cout << "Testing PTree FlipVertical_small..." << endl;

  PNG source;
  source.readFromFile("originals/mix-3x5.png");

  // call the tree constructor
  PTree tree(source);

  // FlipHorizontal tree
  tree.FlipVertical();

  PNG soln_image;
  soln_image.readFromFile("soln-images/soln-flipvertical-mix-3x5.png");

  PNG output = tree.Render();

  output.writeToFile("images/flipvertical-mix-3x5.png");

  REQUIRE(output == soln_image);
}

TEST_CASE("PTree::FlipVertical_large", "[weight=1][part=ptree]") {
  //cout << "Testing PTree FlipVertical_large..." << endl;

  PNG source;
  source.readFromFile("originals/kkkk-256x224.png");

  // call the tree constructor
  PTree tree(source);

  // FlipVertical tree
  tree.FlipVertical();

  PNG soln_image;
  soln_image.readFromFile("soln-images/soln-flipvertical-kkkk.png");

  PNG output = tree.Render();

  output.writeToFile("images/flipvertical-kkkk.png");

  REQUIRE(output == soln_image);
}

TEST_CASE("PTree::Prune_FlipH_FlipV", "[weight=1][part=ptree]") {
  //cout << "Testing PTree Prune_FlipH_FlipV..." << endl;

  PNG source;
  source.readFromFile("originals/ggyhke-256x224.png");

  // call the tree constructor
  PTree tree(source);

  // First prune the tree
  tree.Prune(0.03);

  // FlipHorizontal tree
  tree.FlipHorizontal();

  // FlipVertical tree
  tree.FlipVertical();

  PNG soln_image;
  soln_image.readFromFile("soln-images/soln-prune_003-fliph-flipv-ggyhke.png");

  PNG output = tree.Render();

  output.writeToFile("images/prune_003-fliph-flipv-ggyhke.png");

  REQUIRE(output == soln_image);
}