/*
*  File:        ptree.cpp
*  Description: Implementation of a partitioning tree class for CPSC 221 PA3
*  Date:        2022-03-03 01:53
*
*               ADD YOUR PRIVATE FUNCTION IMPLEMENTATIONS TO THE BOTTOM OF THIS FILE
*/

#include "ptree.h"
#include "hue_utils.h" // useful functions for calculating hue averages
#include "ptree-private.h"

using namespace cs221util;
using namespace std;

// The following definition may be convenient, but is not necessary to use
typedef pair<unsigned int, unsigned int> pairUI;

/////////////////////////////////
// PTree private member functions
/////////////////////////////////

/*
*  Destroys all dynamically allocated memory associated with the current PTree object.
*  You may want to add a recursive helper function for this!
*  POST: all nodes allocated into the heap have been released.
*/
void PTree::Clear() {
  // add your implementation below
  if (root != NULL) {
    clearNode(root);
  }
}

/*
*  Copies the parameter other PTree into the current PTree.
*  Does not free any memory. Should be called by copy constructor and operator=.
*  You may want a recursive helper function for this!
*  PARAM: other - the PTree which will be copied
*  PRE:   There is no dynamic memory associated with this PTree.
*  POST:  This PTree is a physically separate copy of the other PTree.
*/
void PTree::Copy(const PTree& other) {
  root = CopyHelper(other.root);
}

/*
*  Private helper function for the constructor. Recursively builds the tree
*  according to the specification of the constructor.
*  You *may* change this if you like, but we have provided here what we
*  believe will be sufficient to use as-is.
*  PARAM:  im - full reference image used for construction
*  PARAM:  ul - upper-left image coordinate of the currently building Node's image region
*  PARAM:  w - width of the currently building Node's image region
*  PARAM:  h - height of the currently building Node's image region
*  RETURN: pointer to the fully constructed Node
*/
Node* PTree::BuildNode(PNG& im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h) {
  // Create root
  HSLAPixel avgClr = avgColor(im, ul, w, h);
  Node* newNode = new Node(ul, w, h, avgClr, nullptr, nullptr);

  // Temporary width and height variables
  int widthA, heightA;

  // Base case to prevent infinite recursion
  if (w == 1 && h == 1) return newNode;

  // Partition in different ways if height is greater than or less than
  if (h > w) {
    // Build tall node
      if (h%2 == 1) {
        heightA = (h-1)/2;
        newNode->A = BuildNode(im, ul, w, heightA);
        newNode->B = BuildNode(im, make_pair(ul.first, (ul.second + heightA)), w, (heightA + 1));
      } else {
        heightA = h/2;
        newNode->A = BuildNode(im, ul, w, heightA);
        newNode->B = BuildNode(im, make_pair(ul.first, (ul.second + heightA)), w, heightA);
      }
  } else {
    // Build wide node
    if (w%2 == 1) {
        widthA = (w-1)/2;
        newNode->A = BuildNode(im, ul, widthA, h);
        newNode->B = BuildNode(im, make_pair((ul.first + widthA), ul.second), (widthA+1), h);
      } else {
        widthA = w/2;
        newNode->A = BuildNode(im, ul, widthA, h);
        newNode->B = BuildNode(im, make_pair((ul.first + widthA), ul.second), widthA, h);
      }
  }
  return newNode;
}

////////////////////////////////
// PTree public member functions
////////////////////////////////

/*
*  Constructor that builds the PTree using the provided PNG.
*
*  The PTree represents the sub-image (actually the entire image) from (0,0) to (w-1, h-1) where
*  w-1 and h-1 are the largest valid image coordinates of the original PNG.
*  Each node corresponds to a rectangle of pixels in the original PNG, represented by
*  an (x,y) pair for the upper-left corner of the rectangle, and two unsigned integers for the
*  number of pixels on the width and height dimensions of the rectangular sub-image region the
*  node defines.
*
*  A node's two children correspond to a partition of the node's rectangular region into two
*  equal (or approximately equal) size regions which are either tiled horizontally or vertically.
*
*  If the rectangular region of a node is taller than it is wide, then its two children will divide
*  the region into vertically-tiled sub-regions of equal height:
*  +-------+
*  |   A   |
*  |       |
*  +-------+
*  |   B   |
*  |       |
*  +-------+
*
*  If the rectangular region of a node is wider than it is tall, OR if the region is exactly square,
*  then its two children will divide the region into horizontally-tiled sub-regions of equal width:
*  +-------+-------+
*  |   A   |   B   |
*  |       |       |
*  +-------+-------+
*
*  If any region cannot be divided exactly evenly (e.g. a horizontal division of odd width), then
*  child B will receive the larger half of the two subregions.
*
*  When the tree is fully constructed, each leaf corresponds to a single pixel in the PNG image.
* 
*  For the average colour, this MUST be computed separately over the node's rectangular region.
*  Do NOT simply compute this as a weighted average of the children's averages.
*  The functions defined in hue_utils.h and implemented in hue_utils.cpp will be very useful.
*  Computing the average over many overlapping rectangular regions sounds like it will be
*  inefficient, but as an exercise in theory, think about the asymptotic upper bound on the
*  number of times any given pixel is included in an average calculation.
* 
*  PARAM: im - reference image which will provide pixel data for the constructed tree's leaves
*  POST:  The newly constructed tree contains the PNG's pixel data in each leaf node.
*/
PTree::PTree(PNG& im) {
  pair<unsigned int, unsigned int> topLeft = make_pair(0, 0);
  root = BuildNode(im, topLeft, im.width(), im.height());
}

/*
*  Copy constructor
*  Builds a new tree as a copy of another tree.
*
*  PARAM: other - an existing PTree to be copied
*  POST:  This tree is constructed as a physically separate copy of other tree.
*/
PTree::PTree(const PTree& other) {
  Copy(other);
}

/*
*  Assignment operator
*  Rebuilds this tree as a copy of another tree.
*
*  PARAM: other - an existing PTree to be copied
*  POST:  If other is a physically different tree in memory, all pre-existing dynamic
*           memory in this tree is deallocated and this tree is reconstructed as a
*           physically separate copy of other tree.
*         Otherwise, there is no change to this tree.
*/
PTree& PTree::operator=(const PTree& other) {
  if (this != &other) {
    Clear();
    Copy(other);
  }
  // if (other.root == nullptr) {
  //   if (root != nullptr) {
  //     Clear();
  //   }
  //   root = nullptr;
  // } else if (!nodesEqual(root, other.root)) {
  //   Clear();
  //   Copy(other);
  // }
  return *this;
}

/*
*  Destructor
*  Deallocates all dynamic memory associated with the tree and destroys this PTree object.
*/
PTree::~PTree() {
  Clear();
}

/*
*  Traverses the tree and puts the leaf nodes' color data into the nodes'
*  defined image regions on the output PNG.
*  For non-pruned trees, each leaf node corresponds to a single pixel that will be coloured.
*  For pruned trees, each leaf node may cover a larger rectangular region that will be
*  entirely coloured using the node's average colour attribute.
*
*  You may want to add a recursive helper function for this!
*
*  RETURN: A PNG image of appropriate dimensions and coloured using the tree's leaf node colour data
*/
PNG PTree::Render() const {
  // Render PNG for non-pruned tree
  PNG img = PNG(root->width, root->height);

  // Call helper to colour PNG
  RenderHelper(img, root);
  return img;
}

/*
*  Trims subtrees as high as possible in the tree. A subtree is pruned
*  (its children are cleared/deallocated) if ALL of its leaves have colour
*  within tolerance of the subtree root's average colour.
*  Pruning criteria should be evaluated on the original tree, and never on a pruned
*  tree (i.e. we expect that Prune would be called on any tree at most once).
*  When processing a subtree, you should determine if the subtree should be pruned,
*  and prune it if possible before determining if it has subtrees that can be pruned.
* 
*  You may want to add (a) recursive helper function(s) for this!
*
*  PRE:  This tree has not been previously pruned (and is not copied/assigned from a tree that has been pruned)
*  POST: Any subtrees (as close to the root as possible) whose leaves all have colour
*        within tolerance from the subtree's root colour will have their children deallocated;
*        Each pruned subtree's root becomes a leaf node.
*/
void PTree::Prune(double tolerance) {
  PruneHelper(root, tolerance); 
}

/*
*  Returns the total number of nodes in the tree.
*  This function should run in time linearly proportional to the size of the tree.
*
*  You may want to add a recursive helper function for this!
*/
int PTree::Size() const {
  return (root == nullptr) ? -1 : SizeHelper(root);
}

/*
*  Returns the total number of leaf nodes in the tree.
*  This function should run in time linearly proportional to the size of the tree.
*
*  You may want to add a recursive helper function for this!
*/
int PTree::NumLeaves() const {
  return (root == nullptr) ? -1 : NumLeavesHelper(root);
}

/*
*  Rearranges the nodes in the tree, such that a rendered PNG will be flipped horizontally
*  (i.e. mirrored over a vertical axis).
*  This can be achieved by manipulation of the nodes' member attribute(s).
*  Note that this may possibly be executed on a pruned tree.
*  This function should run in time linearly proportional to the size of the tree.
*
*  You may want to add a recursive helper function for this!
*
*  POST: Tree has been modified so that a rendered PNG will be flipped horizontally.
*/
void PTree::FlipHorizontal() {
  // add your implementation below
  
}

/*
*  Like the function above, rearranges the nodes in the tree, such that a rendered PNG
*  will be flipped vertically (i.e. mirrored over a horizontal axis).
*  This can be achieved by manipulation of the nodes' member attribute(s).
*  Note that this may possibly be executed on a pruned tree.
*  This function should run in time linearly proportional to the size of the tree.
*
*  You may want to add a recursive helper function for this!
*
*  POST: Tree has been modified so that a rendered PNG will be flipped vertically.
*/
void PTree::FlipVertical() {
  // add your implementation below
  
}

/*
    *  Provides access to the root of the tree.
    *  Dangerous in practice! This is only used for testing.
    */
Node* PTree::GetRoot() {
  return root;
}

//////////////////////////////////////////////
// PERSONALLY DEFINED PRIVATE MEMBER FUNCTIONS
//////////////////////////////////////////////


// Computes Average Color
HSLAPixel PTree::avgColor(PNG& im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h) {
  double hueAccumX = 0.0;
  double hueAccumY = 0.0;
  double hueAccum = 0.0;
  double satAccum = 0.0;
  double lumAccum = 0.0;
  HSLAPixel* orig;

  unsigned int endX = ul.first + w;
  unsigned int endY = ul.second + h;

  for (unsigned int x = ul.first; x < endX; x++) {
    for (unsigned int y = ul.second; y < endY; y++) {
      if (x == im.width() || y == im.height()) {
        break;
      }
      orig = im.getPixel(x, y);
      hueAccumX += Deg2X(orig->h);
      hueAccumY += Deg2Y(orig->h);
      satAccum += orig->s;
      lumAccum += orig->l;
    }
  }

  hueAccumX /= w;
  hueAccumY /= h;
  hueAccum = XY2Deg(hueAccumX, hueAccumY);
  lumAccum /= (h * w);
  satAccum /= (h * w);

  return HSLAPixel(hueAccum, satAccum, lumAccum);
}

// Helper function for Size()
int PTree::SizeHelper(Node* subroot) const {
  if (subroot == NULL) return 0;
  return (SizeHelper(subroot->A) + 1 + SizeHelper(subroot->B));
}

// Helper function for NumLeaves()
int PTree::NumLeavesHelper(Node* subroot) const {
  if (subroot->A == NULL) return 1;
  if (subroot->B == NULL) return 1;
  return (NumLeavesHelper(subroot->A) + NumLeavesHelper(subroot->B));
}

// Helper function for Copy()
Node* PTree::CopyHelper(Node* other) {
  // Create pointer to copied node (identical to other)
  Node* copied = new Node();
  copied->upperleft = make_pair(other->upperleft.first, other->upperleft.second);
  copied->width = other->width;
  copied->height = other->height;
  copied->avg = other->avg;

  if (other->A && other->B) {
    copied->A = CopyHelper(other->A);
    copied->B = CopyHelper(other->B);
  } else {
    copied->A = nullptr;
    copied->B = nullptr;
  }

  root = copied;
  return root;
}

// Helper function for Clear()
void PTree::clearNode(Node* curr) {
  if (!curr) return;

  clearNode(curr->A);
  clearNode(curr->B);
  curr->A = nullptr;
  curr->B = nullptr;
  delete curr;
  curr = nullptr;

  // if (curr.A != nullptr) {
  //   clearNode(*(curr.A));
  // }
  // if (curr.B != nullptr) {
  //   clearNode(*(curr.B));
  // }
  // if (curr.A != nullptr) {
  //   delete(curr.A);
  // }
  // if (curr.B != nullptr) {
  //   delete(curr.B);
  // }
}

// Helper function for operator=()
bool PTree::nodesEqual(Node * orig, Node * other) {
  if (orig == NULL && other == NULL) {
    return true;
  }

  if (orig->height == other->height && orig->width == other->width && orig->avg == other->avg) {
    return (nodesEqual(orig->A, other->A) && nodesEqual(orig->A, other->B));
  } else  {
    return false;
  }
}

// Helper function for Render()
void PTree::RenderHelper(PNG& image, Node* subroot) const {
  // Base case to prevent infinite recursion
  if (!subroot) return;

  for (unsigned int x = 0; x < subroot->width; x++) {
    for (unsigned int y = 0; y < subroot->height; y++) {
      HSLAPixel* toFill = image.getPixel(subroot->upperleft.first + x, subroot->upperleft.second + y);
      *toFill = subroot->avg;
    }
  }

  // Recursively call on subnodes
  RenderHelper(image, subroot->A);
  RenderHelper(image, subroot->B);
}

/*
*  Trims subtrees as high as possible in the tree. A subtree is pruned
*  (its children are cleared/deallocated) if ALL of its leaves have colour
*  within tolerance of the subtree root's average colour.
*  Pruning criteria should be evaluated on the original tree, and never on a pruned
*  tree (i.e. we expect that Prune would be called on any tree at most once).
*  When processing a subtree, you should determine if the subtree should be pruned,
*  and prune it if possible before determining if it has subtrees that can be pruned.
* 
*  You may want to add (a) recursive helper function(s) for this!
*
*  PRE:  This tree has not been previously pruned (and is not copied/assigned from a tree that has been pruned)
*  POST: Any subtrees (as close to the root as possible) whose leaves all have colour
*        within tolerance from the subtree's root colour will have their children deallocated;
*        Each pruned subtree's root becomes a leaf node.
*/
void PTree::PruneHelper(Node* subroot, double tolerance) {
  // Base case prevents infinite recursion
  if (!subroot) return;

  // Determine if pruning should occur
  if (ShouldPrune(subroot->avg, subroot, tolerance)) {
    clearNode(subroot->A);
    clearNode(subroot->B);
    subroot->A = nullptr;
    subroot->B = nullptr;
  } else {
    PruneHelper(subroot->A, tolerance);
    PruneHelper(subroot->B, tolerance);
  }
}

bool PTree::ShouldPrune(HSLAPixel rootAvgColor, Node* subroot, double tolerance) {
  if (!subroot) return true;

  if (!subroot->A && !subroot->B) {
    return rootAvgColor.dist(subroot->avg) <= tolerance;
  } else {
    return ShouldPrune(rootAvgColor, subroot->A, tolerance) && ShouldPrune(rootAvgColor, subroot->B, tolerance);
  }
}
