#include "huffman.h"
int main(int argc, char const *argv[])
{

    string filename;
    cout << "Enter a filename" << endl;
    cin >> filename;

    ifstream file(filename);
    HuffmanTree ht;
    ht.createTree(file);
    ht.printCodes();
    unordered_map<char, string> codes = ht.getCodes();
    return 1;
}
