// #include <iostream>
// #include <fstream>
// #include <map>
// #include <queue>
// using namespace std;

// // Define a Huffman tree node
// struct Node {
//     char data;
//     int freq;
//     Node* left;
//     Node* right;
// };

// // Compare function for priority queue
// struct Compare {
//     bool operator()(Node* a, Node* b) {
//         return a->freq > b->freq;
//     }
// };

// // Build Huffman tree
// Node* buildHuffmanTree(map<char, int>& freqMap) {
//     priority_queue<Node*, vector<Node*>, Compare> pq;
//     for (auto& entry : freqMap) {
//         pq.push(new Node{entry.first, entry.second, nullptr, nullptr});
//     }

//     while (pq.size() > 1) {
//         Node* left = pq.top(); pq.pop();
//         Node* right = pq.top(); pq.pop();
//         Node* newNode = new Node{'\0', left->freq + right->freq, left, right};
//         pq.push(newNode);
//     }
//     return pq.top();
// }

// // Generate Huffman codes
// void generateHuffmanCodes(Node* root, string code, map<char, string>& huffmanCodes) {
//     if (!root) return;
//     if (root->data != '\0') {
//         huffmanCodes[root->data] = code;
//     }
//     generateHuffmanCodes(root->left, code + "0", huffmanCodes);
//     generateHuffmanCodes(root->right, code + "1", huffmanCodes);
// }

// int main() {
//     ifstream inputFile("input.txt");
//     map<char, int> freqMap;
//     char ch;
//     while (inputFile >> noskipws >> ch) {
//         freqMap[ch]++;
//     }
//     inputFile.close();

//     Node* root = buildHuffmanTree(freqMap);
//     map<char, string> huffmanCodes;
//     generateHuffmanCodes(root, "", huffmanCodes);

//     ofstream outputFile("encoded_output.bin", ios::binary);
//     inputFile.open("input.txt");
//     while (inputFile >> noskipws >> ch) {
//         outputFile << huffmanCodes[ch];
//     }
//     inputFile.close();
//     outputFile.close();

//     cout << "File compressed successfully! Encoded data saved in 'encoded_output.bin'." << endl;
//     return 0;
// }


#include <iostream>
#include <fstream>
#include <map>
#include <queue>
using namespace std;

// Define a Huffman tree node
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;
};

// Compare function for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Build Huffman tree
Node* buildHuffmanTree(map<char, int>& freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& entry : freqMap) {
        pq.push(new Node{entry.first, entry.second, nullptr, nullptr});
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* newNode = new Node{'\0', left->freq + right->freq, left, right};
        pq.push(newNode);
    }
    return pq.top();
}

// Generate Huffman codes
void generateHuffmanCodes(Node* root, string code, map<char, string>& huffmanCodes) {
    if (!root) return;
    if (root->data != '\0') {
        huffmanCodes[root->data] = code;
    }
    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

int main() {
    ifstream inputFile("input.txt");
    map<char, int> freqMap;
    char ch;
    while (inputFile >> noskipws >> ch) {
        freqMap[ch]++;
    }
    inputFile.close();

    Node* root = buildHuffmanTree(freqMap);
    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Write character frequencies and encodings to the output file
    ofstream outputFile("encoded_output.bin", ios::binary);
     outputFile << huffmanCodes.size() << endl;
    for (const auto& entry : huffmanCodes) {
        outputFile << entry.first << " " << entry.second << endl;
    }

    // Append the encoded data
    inputFile.open("input.txt");
    while (inputFile >> noskipws >> ch) {
        outputFile << huffmanCodes[ch];
    }
    inputFile.close();
    outputFile.close();

    cout << "File compressed successfully! Encoded data saved in 'encoded_output.bin'." << endl;
    return 0;
}
