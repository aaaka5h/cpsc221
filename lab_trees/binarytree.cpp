/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file, as well as binarytree.h.
 */

#include <iostream>

using namespace std;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function, with an additional
 * Node* parameter to allow for recursive calls. NOTE: use this as an example
 * for writing your own private helper functions.
 * @param subRoot
 * @return The height of the subtree.
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    printLeftToRight(root);
    // Do not remove this line - used for correct print output
    cout << endl;
}

template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    if (subRoot == nullptr)
        return;

    printLeftToRight(subRoot->left);
    cout << to_string(subRoot->elem) << " ";
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 * (i.e. not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) 
{
  if (subRoot == nullptr) {
    return;
  }

  mirror(subRoot->left);
  mirror(subRoot->right);
  swap(subRoot->left, subRoot->right);
}

/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
  printPaths(root, "Path:");
}

template <typename T>
void BinaryTree<T>::printPaths(const Node* subRoot, string pathSoFar) const
{
  if (subRoot == nullptr) {
      return;
  }

  pathSoFar += " " + to_string(subRoot->elem);

  if (subRoot->left == nullptr && subRoot->right == nullptr) {
    cout << pathSoFar << endl;
  } else {
    printPaths(subRoot->left, pathSoFar);
    printPaths(subRoot->right, pathSoFar);
  }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root.
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
  return sumDistances(root, 0);
}

template <typename T>
int BinaryTree<T>::sumDistances(const Node* subRoot, int dist) const
{
  if (subRoot == nullptr) {
    return 0;
  }
  return dist + sumDistances(subRoot->left, dist + 1) + sumDistances(subRoot->right, dist + 1);
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
  return isOrdered(root, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot, T min, T max) const
{
  if (subRoot == nullptr) {
    return true;
  }

  return (min <= subRoot->elem && subRoot->elem <= max) &&
   isOrdered(subRoot->left, min, subRoot->elem) &&
   isOrdered(subRoot->right, subRoot->elem, max);
}

