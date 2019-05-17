#include "b-link-tree.hpp"

int main()
{
    BLinkTree<int, int> tree;
    int x;
    while (std::cin >> x) tree.insert(x, x);
    return 0;
}
