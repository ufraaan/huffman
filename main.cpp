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

/*
    recursive function that walks through the tree and builds the code
        1.start at root
        2. go left -> add "0"
        3. go right -> add "1"
        4. when we reach a char. node --> save code for that char.
*/
void generateCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    // we reached leaf node
    if (root->left == nullptr && root->right == nullptr) {
        // cout << root->ch << " : " << code << endl;
        codes[root->ch] = code;
        return;
    }

    // go left and add 0
    generateCodes(root->left, code + "0", codes);
    
    // go right and add 1
    generateCodes(root->right, code + "1", codes);
}

string decode(Node* root, string encoded) {
    string decoded = "";
    Node* current = root; // tells where we are currently in the tree.. initially at root

    for (char bit : encoded) { // for every bit.. like for every char.. calling 'bit' cus 0,1.
        if (bit == '0') {
            current = current->left; // go left
        } else {
            current = current->right; // go right
        }
        // check if leaf (leaves represent chars.)
        if (current->left == nullptr && current->right == nullptr) {
            decoded += current->ch; // add that character
            current = root; // go back to root (cus we will be at leaf if not done). reset essentially.
        }
    }
    return decoded;
}

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

    unordered_map<char, string> codes; // map to store the huffman codes
    generateCodes(root, "", codes);

    // encode the text
    string encoded = ""; 
    for (char ch : text) { // this is original text defined in beginning of main()
        encoded += codes[ch]; // append this char's huffman code
    }
    cout << "encoded:" << encoded << endl; // concatenated encoded string of huffman code

    string decoded = decode(root, encoded);
    cout << "decoded:" << decoded << endl;
    return 0;
}