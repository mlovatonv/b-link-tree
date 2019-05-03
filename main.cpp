#include "b-link-tree.hpp"

int main()
{
    // BLinkNode<int, int> node(LEAF);
    // node.insert(5, 1);
    // node.insert(7, 2);
    // node.insert(1, 3);
    // node.insert(10, 4);
    // node.insert(0, 5);
    // node.insert(2, 6);
    // node.insert(20, 7);
    // node.insert(3, 8);
    // node.print();

    BLinkTree<int, int> tree;
    tree.insert(5, 1);
    tree.insert(7, 2);
    tree.insert(1, 3);
    tree.insert(10, 4);
    tree.insert(0, 5);
    tree.insert(2, 6);
    tree.insert(20, 7);
    tree.insert(3, 8);
    tree.print();
    return 0;
}
