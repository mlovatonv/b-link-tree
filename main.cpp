//#include "b-link-tree.hpp"
#include "b-link-node.hpp"

int main()
{
    BLinkNode<int> node;
    node.insert(5);
    node.insert(7);
    node.insert(1);
    node.insert(10);
    node.Print();
    //tree.print();
    return 0;
}
