#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <queue>
using namespace std;

class HuffmanTree;
class Compare;

class Node
{
private:
    double probability;
    char character;
    Node *left;
    Node *right;

public:
    Node()
    {
        probability = 0;
        left = nullptr;
        right = nullptr;
    };
    Node(char c, double prob)
    {
        this->character = c;
        this->probability = prob;
        left = right = nullptr;
    };
    Node(char c, double prob, Node *left, Node *right)
    {
        this->character = c;
        this->probability = prob;
        this->left = left;
        this->right = right;
    };
    friend class HuffmanTree;
    friend class Compare;
};

class Compare
{
public:
    bool operator()(Node *a, Node *b)
    {
        if (a->probability > b->probability)
            return true;
        return false;
    }
};

class HuffmanTree
{
private:
    Node *root;
    unordered_map<char, string> codes;
    priority_queue<Node *, vector<Node *>, Compare> nodeQueue;

public:
    HuffmanTree() : root(0){};
    void createTree(ifstream &file);
    void readFile(ifstream &file);
    void printPriorityQueue();
    void assignCodes(Node *node, string code = "");
    void printCodes();
};

void HuffmanTree::readFile(ifstream &file)
{
    char ch;
    unordered_map<char, int> charCounts;
    if (!file.is_open())
    {
        cerr << "Error opening file: " << endl;
        return;
    }

    while (file.get(ch))
        if (isalnum(ch))
            charCounts[ch]++;

    int totalChars = 0;
    for (const auto &[ch, count] : charCounts)
        totalChars += count;

    for (const auto &[ch, count] : charCounts)
    {
        double probability = static_cast<double>(count) / totalChars;
        nodeQueue.push(new Node(ch, probability));
    }
}

void HuffmanTree::createTree(ifstream &file)
{
    readFile(file);

    while (nodeQueue.size() != 1)
    {
        Node *left = nodeQueue.top();
        nodeQueue.pop();

        Node *right = nodeQueue.top();
        nodeQueue.pop();

        Node *newNode = new Node('$', left->probability + right->probability, left, right);
        root = newNode;
        nodeQueue.push(root);
    }
    assignCodes(root);
}

void HuffmanTree::assignCodes(Node *node, string code)
{
    if (node->right != nullptr && node->left != nullptr)
    {
        assignCodes(node->left, code + "0");
        assignCodes(node->right, code + "1");
    }
    else
    {
        codes[node->character] = code;
    }
}

void HuffmanTree::printCodes()
{
    for (const auto &[ch, str] : codes)
    {
        cout << ch << " : " << str << endl;
    }
}

void HuffmanTree::printPriorityQueue()
{
    int size = nodeQueue.size();
    for (int i = 0; i < size; i++)
    {
        Node *temp = nodeQueue.top();
        nodeQueue.pop();
        cout << temp->character << " : " << temp->probability << endl;
    }
}
