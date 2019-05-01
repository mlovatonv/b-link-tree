//#include "b-link-tree.hpp"
#include "b-link-node.hpp"

int main()
{
    BLinkNode<int> tree;
    tree.insert(2);
    tree.insert(4);
    tree.insert(5);
    tree.insert(3);
    tree.Print();
    //tree.print();
    return 0;
}
