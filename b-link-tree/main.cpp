#include "b-link-tree.hpp"

int main()
{
    BLinkTree<int, std::string> tree;
    tree.insert(2, "maria");
    tree.insert(100, "indhira");
    std::cout << tree.search(2) << "\n";
    return 0;
}
