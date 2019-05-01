//#include "b-link-tree.hpp"
#include "b-link-node.hpp"

int main()
{
    BLinkNode<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(1);
    tree.Print();
    //tree.print();
    return 0;
}
