/*
*  File:        ptree-private.h
*  Description: Private functions for the PTree class
*  Date:        2022-03-06 03:30
*
*               DECLARE YOUR PTREE PRIVATE MEMBER FUNCTIONS HERE
*/

#ifndef _PTREE_PRIVATE_H_
#define _PTREE_PRIVATE_H_

/////////////////////////////////////////////////
// DEFINE YOUR PRIVATE MEMBER FUNCTIONS HERE
//
// Just write the function signatures.
//
// Example:
//
// Node* MyHelperFunction(int arg_a, bool arg_b);
//
/////////////////////////////////////////////////
HSLAPixel avgColor(PNG& im, pair<unsigned int, unsigned int> ul, unsigned int w, unsigned int h);
int SizeHelper(Node* subroot) const;
int NumLeavesHelper(Node* subroot) const;
Node* CopyHelper(Node* other);
void clearNode(Node* curr);
bool nodesEqual(Node * orig, Node * other);
void RenderHelper(PNG& image, Node* subroot) const;
void PruneHelper(Node* subroot, double tolerance);
bool ShouldPrune(HSLAPixel rootAvgColor, Node* subroot, double tolerance);


#endif
