#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;


struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

int main() {

    string text = "banana";
    // count freq. of every letter
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // array to store values of pointers of nodes
    vector<Node*> nodes;
    
    // create node for every pair
    for (auto pair : freq) {
        Node* node = new Node(pair.first, pair.second);
        nodes.push_back(node);
    }

    // create min-heap of node ptrs
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // put every node into heap
    for (Node* node : nodes) {
        minHeap.push(node);
    }

    // check node with smallest freq.
    Node* smallest = minHeap.top();
    cout << smallest->ch << " : "
         << smallest->freq << endl; 

    return 0;
}