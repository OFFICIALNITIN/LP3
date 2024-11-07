#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

// Define a structure for the Huffman Tree nodes
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Function to build the Huffman Tree
Node* buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (auto pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        int sum = left->freq + right->freq;
        Node* newNode = new Node('\0', sum);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    return minHeap.top();
}

// Function to generate Huffman codes
void generateHuffmanCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to encode a given text using Huffman coding
string encodeText(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encodedText = "";
    for (char ch : text) {
        encodedText += huffmanCodes.at(ch);
    }
    return encodedText;
}

// Function to decode a given encoded text using Huffman tree
string decodeText(const string& encodedText, Node* root) {
    string decodedText = "";
    Node* currentNode = root;
    for (char bit : encodedText) {
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        if (!currentNode->left && !currentNode->right) {
            decodedText += currentNode->ch;
            currentNode = root;
        }
    }
    return decodedText;
}

int main() {
    string text;
    cout << "Enter text to encode: ";
    getline(cin, text);

    // Frequency map
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // Build Huffman Tree and generate codes
    Node* root = buildHuffmanTree(freqMap);
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    cout << "\nHuffman Codes:\n";
    for (auto pair : huffmanCodes) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Encode the text
    string encodedText = encodeText(text, huffmanCodes);
    cout << "\nEncoded Text: " << encodedText << endl;

    // Decode the text using the original Huffman tree root
    string decodedText = decodeText(encodedText, root);
    cout << "\nDecoded Text: " << decodedText << endl;

    return 0;
}