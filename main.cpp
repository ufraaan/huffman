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

// priority_queue expects a Type for the third template parameter
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; //  smaller freq = higher priority
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

    // // check node with smallest freq.
    // Node* smallest = minHeap.top();
    // cout << smallest->ch << " : "
    //      << smallest->freq << endl; 


    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop(); // cus we already saved the min. at that state
        //same for right for next min.
        Node* right = minHeap.top();
        minHeap.pop();

        // now create new node to combine
        Node* parent = new Node('\0', left->freq + right-> freq); // left.freq is 1, right.freq is 2. so total 3.
        // now our node will look like ['\0', 3]. \0 cus node is not representing a character, we dont need that.

        // now connect old nodes to the new one
        parent->left = left; // the left we got from minHeap.top()
        parent->right = right; // the right we got from minHeap.top()

        // put this newly created node 'parent' back to the minHeap.
        minHeap.push(parent);
    }

    // points to the top of the huffman tree
    Node* root = minHeap.top();

    return 0;
}