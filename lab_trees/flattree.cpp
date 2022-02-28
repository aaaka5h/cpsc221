using namespace std;

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 * {X 1 2 3 4 5 6 7}
 * {  4 2 5 1 6 3 7}
 */
template <typename T>
void FlatTree<T>::printLeftToRight() const {
    // Your code here
    cout << endl;
}

template <typename T>
T& FlatTree<T>::getElement(const string& path) {
    // Your code here

    return data.front(); // STUB, delete this line
}

template <typename T>
void FlatTree<T>::fromBinaryTree(const BinaryTree<T>& tree) {
    // Your code here

}

template <typename T>
BinaryTree<T> FlatTree<T>::toBinaryTree() const {
    // Your code here
    return BinaryTree<T>();
}

