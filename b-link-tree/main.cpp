#include "b-link-tree.hpp"

int main()
{
    BLinkTree<int, int> tree;
    tree.insert(5, 1);
    tree.insert(10000, 2);
    tree.insert(1, 3);
    tree.insert(10, 4);
    tree.insert(0, 5);
    tree.insert(2, 6);
    tree.insert(123, 7);
    tree.insert(12, 8);
    tree.insert(100, 4);
    tree.insert(20, 5);
    tree.insert(11, 6);
    tree.insert(32, 7);
    tree.insert(8, 8);
    tree.print();
    return 0;
}
