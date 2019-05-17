#include "b-link-tree.hpp"
#include <fstream>
#include <string>
#include <sstream>

int main()
{
    BLinkTree<int, std::string> tree;
    // int x;
    // while (std::cin >> x) tree.insert(x, x);
    const std::string path = "/home/mlovatonv/utec/ada/b-link-tree/b-link-tree-gui/data.txt";
    std::ifstream infile(path);
    std::string line;
    int key;
    std::string data;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        if (!(iss >> key >> data)) { break; } // error
        tree.insert(key, data);
    }
    std::cout << "\n";
    tree.print();
    return 0;
}
