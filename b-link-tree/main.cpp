#include "b-link-tree.hpp"
#include <fstream>
#include <string>
#include <sstream>

int main()
{
    BLinkTree<int, std::string> tree;
    std::ifstream infile("../b-link-tree-gui/data.txt");
    std::string line;
    int key;
    std::string data;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        if (!(iss >> key >> data)) { break; } // error
        tree.insert(key, data);
    }
    std::cout << tree.search(1) << "\n";
    return 0;
}
