//#include "b-link-tree.hpp"
#include "b-link-node.hpp"

int main()
{
    BLinkNode<int> node(LEAF);
    node.insert(5);
    node.insert(7);
    node.insert(1);
    node.insert(10);
    node.insert(0);
    node.insert(2);
    node.insert(20);
    node.insert(3);
    node.print();
    //tree.print();
    return 0;
}
