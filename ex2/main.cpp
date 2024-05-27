#include <iostream>
#include <fstream>
#include "encoding.h"

using namespace std;

int main() {
    ifstream inputFile("message.in");
    if (!inputFile.is_open()) {
        cerr << "Error opening message.in file." << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    BST bst = buildFrequencyBST(text);

    EncodingTree encodingTree(bst);

    if (encodingTree.root == nullptr) {
        cerr << "Error: Encoding tree root is null." << endl;
        return 1;
    }

    string encodedMessage = encode(encodingTree.root, text);

    ofstream encodedOutFile("encoded.out");
    if (!encodedOutFile.is_open()) {
        cerr << "Error opening encoded.out file." << endl;
        return 1;
    }
    encodedOutFile << encodedMessage;
    encodedOutFile.close();

    ifstream encodedInFile("encoded.in");
    if (!encodedInFile.is_open()) {
        cerr << "Error opening encoded.in file." << endl;
        return 1;
    }
    string encodedInput((istreambuf_iterator<char>(encodedInFile)), istreambuf_iterator<char>());
    encodedInFile.close();

    string decodedMessage = decode(encodingTree.root, encodedInput);

    ofstream decodedOutFile("message.out");
    if (!decodedOutFile.is_open()) {
        cerr << "Error opening message.out file." << endl;
        return 1;
    }
    decodedOutFile << decodedMessage;
    decodedOutFile.close();

    return 0;
}
