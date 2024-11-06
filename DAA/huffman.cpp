#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>

using namespace std;

//Node structure for the huffman tree
struct Node{
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character, int frequency): ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};

//Comparator for priority queue (min-heap)
struct Compare {
    bool operator()(Node* left, Node* right){
        return left->freq > right->freq;
    }
};

//Function to generate the Huffman codes
void generateHuffmanCodes(Node* root, string code, unordered_map<char,string>& huffmanCodes){
    if(!root) return;

    //If this node is a leaf node
    if(!root->left && !root->right){
        huffmanCodes[root->ch] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

//Function to  build the huffman tree and generate codes
unordered_map<char,string> huffmanEncoding(const string& text){
    //Count frequency of each character
    unordered_map<char,int> freq;
    for(char ch : text){
        freq[ch]++;
    }

    //Create a priority queue to build the huffman tree
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for(auto pair:freq){
        minHeap.push(new Node(pair.first, pair.second));
    }

    //Build the huffman tree
    while(minHeap.size() > 1){
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        //Create a new internal node with frequency equal to the sum of the two nodes
        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    //The root of the huffman tree
    Node* root = minHeap.top();

    //Generate Huffman codes
    unordered_map<char,string> huffmanCodes;
    generateHuffmanCodes(root,"",huffmanCodes);

    return huffmanCodes;
}

//Function to encode a given text using Huffman coding
string encodeText(const string& text, const unordered_map<char,string>& huffmanCodes){
    string encodeText = "";
    for(char ch:text){
        encodeText += huffmanCodes.at(ch);
    }

    return encodeText;
}

//Function to decode a given encoded text using huffman tree
string decodeText(const string& encodedText, Node* root){
    string decodeText = " ";
    Node* currentNode = root;
    for(char bit : encodedText){
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;

        //If we reach a leaf node
        if(!currentNode->left && !currentNode->right){
            decodeText += currentNode->ch;
            currentNode = root;
        }
    }

    return decodeText;
}

int main(){
    string text;
    cout<<"Enter text to encode: ";
    getline(cin,text);

    //Build Huffman Tree and generate codes
    unordered_map<char,string> huffmanCodes = huffmanEncoding(text);

    cout<<"\nHuffman Code:\n";
    for(auto pair : huffmanCodes){
        cout<<pair.first<<" : "<<pair.second<<endl;
    }

    //Encode the text
    string encodedText = encodeText(text, huffmanCodes);
    cout<<"\nEncoded Text: "<<encodedText<<endl;

    //Decode the text
    //Rebuild Huffman tree to decode
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for(auto pair : huffmanCodes){
        minHeap.push(new Node(pair.first, 1));
    }

    //Decode the text
    string decodetext = decodeText(encodedText, minHeap.top());
    cout<<"\nDecoded Text: "<<decodetext<<endl;

    return 0;
}

//Input
// Enter text to encode: aaabbc


//Output
// Huffman Code:
// b : 11
// c : 10
// a : 0

// Encoded Text: 000111110