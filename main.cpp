//#include "b-link-tree.hpp"
#include "b-link-node.hpp"

int main()
{
    BLinkNode<int, int> node(LEAF);
    node.insert(5, 1);
    node.insert(7, 2);
    node.insert(1, 3);
    node.insert(10, 4);
    node.insert(0, 5);
    node.insert(2, 6);
    node.insert(20, 7);
    node.insert(3, 8);
    node.print();
    //tree.print();
    return 0;
}
