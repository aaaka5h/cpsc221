#ifndef FLATTREE_H
#define FLATTREE_H

template <class T>
struct FlatTree {
  vector<T> data;
  FlatTree(): data(1) {}
  FlatTree(const vector<T>& es): data(es.size()+1) {
    std::copy(es.begin(), es.end(), data.begin()+1);
  }
  /**
   * Same as function in BinaryTree, see binarytree.h
   **/
  void printLeftToRight() const;
  /**
   * Get the element from following the given path string.
   * You may assume the path string is valid
   * - contains only 'L' and 'R'
   * - the represented path leads to an existing element in the tree
   * Example:
   *            __ A __
   *         __/       \__
   *       B               E
   *     /   \
   *   C       D
   *
   * getElement("")   => A
   * getElement("R")  => E
   * getElement("LL") => C
   **/
  T& getElement(const string&);
  /**
   * Construct a FlatTree with the same structure as the given BinaryTree.
   * the existing tree is destroyed.
   * you may assume that the input tree is complete.
   **/
  void fromBinaryTree(const BinaryTree<T>&);
  /**
   * Construct a BinaryTree with the same structure as this tree.
   **/
  BinaryTree<T> toBinaryTree() const;
};
#include "flattree.cpp"
#endif
