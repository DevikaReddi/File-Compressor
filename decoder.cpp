// #include <iostream>
// #include <fstream>
// #include <map>
// #include <string>
// using namespace std;

// // Define a Huffman tree node
// struct Node {
//     char data;
//     Node* left;
//     Node* right;
// };

// // Build Huffman tree from the encoded data
// Node* buildHuffmanTree(ifstream& encodedFile) {
//     char ch;
//     encodedFile >> noskipws >> ch;
//     if (ch == '1') {
//         Node* newNode = new Node{'\0', nullptr, nullptr};
//         newNode->left = buildHuffmanTree(encodedFile);
//         newNode->right = buildHuffmanTree(encodedFile);
//         return newNode;
//     } else {
//         return new Node{ch, nullptr, nullptr};
//     }
// }

// // Decode the encoded data using the Huffman tree
// void decodeHuffmanData(Node* root, ifstream& encodedFile, ofstream& decodedOutput) {
//     Node* curr = root;
//     char bit;
//     while (encodedFile >> noskipws >> bit) {
//         if (bit == '0') {
//             curr = curr->left;
//         } else {
//             curr = curr->right;
//         }
//         if (curr->data != '\0') {
//             decodedOutput << curr->data;
//             curr = root;
//         }
//     }
// }

// int main() {
//     ifstream encodedFile("encoded_output.bin", ios::binary);
//     ofstream decodedOutput("decoded_output.bin");
//     Node* root = buildHuffmanTree(encodedFile);
//     decodeHuffmanData(root, encodedFile, decodedOutput);

//     cout << "File decoded successfully! Decoded data saved in 'decoded_output.bin'." << endl;
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <map>
#include <string>

struct MinHeapNode {
    char data;
    MinHeapNode* left;
    MinHeapNode* right;
    MinHeapNode(char data) {
        left = right = nullptr;
        this->data = data;
    }
};

MinHeapNode* buildHuffmanTree(const std::map<char, std::string>& codes) {
    MinHeapNode* root = new MinHeapNode('$');
    for (const auto& entry : codes) {
        MinHeapNode* curr = root;
        for (char c : entry.second) {
            if (c == '0') {
                if (!curr->left)
                    curr->left = new MinHeapNode('$');
                curr = curr->left;
            } else {
                if (!curr->right)
                    curr->right = new MinHeapNode('$');
                curr = curr->right;
            }
        }
        curr->data = entry.first;
    }
    return root;
}

std::string decodeHuffman(MinHeapNode* root, const std::string& encodedData) {
    std::string decodedData;
    MinHeapNode* curr = root;
    for (char c : encodedData) {
        if (c == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->data != '$') {
            decodedData += curr->data;
            curr = root;
        }
    }
    return decodedData;
}

int main() {
    // Read the encoded data from the file "encoded_output.bin"
    std::ifstream inputFile("encoded_output.bin", std::ios::binary);
    std::string encodedData((std::istreambuf_iterator<char>(inputFile)),
                            std::istreambuf_iterator<char>());
    inputFile.close();

    // Read the character encodings (modify this part according to your input)
    std::map<char, std::string> codes;
    codes['a'] = "010";
    codes['b'] = "110";
    // Add more character encodings as needed

    // Build Huffman tree
    MinHeapNode* root = buildHuffmanTree(codes);

    // Decode the encoded data
    std::string decodedData = decodeHuffman(root, encodedData);
    std::cout << "Decoded data: " << decodedData << std::endl;

    return 0;
}
