#ifndef ENCODING_H
#define ENCODING_H

#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TreeNode {
public:
    char key;
    int freq;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char k, int f) : key(k), freq(f), left(nullptr), right(nullptr) {}
};

class BST {
public:
    TreeNode* root;

    BST() : root(nullptr) {}

    void insert(char key, int freq) {
        root = insertRec(root, key, freq);
    }

    TreeNode* removeMin() {
        if (!root) return nullptr;
        TreeNode* minNode = nullptr;
        root = removeMinRec(root, minNode);
        return minNode;
    }

private:
    TreeNode* insertRec(TreeNode* node, char key, int freq) {
        if (!node) return new TreeNode(key, freq);
        if (freq < node->freq)
            node->left = insertRec(node->left, key, freq);
        else
            node->right = insertRec(node->right, key, freq);
        return node;
    }

    TreeNode* removeMinRec(TreeNode* node, TreeNode*& minNode) {
        if (!node->left) {
            minNode = node;
            return node->right;
        }
        node->left = removeMinRec(node->left, minNode);
        return node;
    }
};

class EncodingTree {
public:
    TreeNode* root;

    EncodingTree(BST& bst) {
        auto comp = [](TreeNode* a, TreeNode* b) { return a->freq > b->freq; };
        priority_queue<TreeNode*, vector<TreeNode*>, decltype(comp)> pq(comp);

        while (TreeNode* minNode = bst.removeMin()) {
            pq.push(minNode);
        }

        if (pq.empty()) {
            root = nullptr;
            return;
        }

        while (pq.size() > 1) {
            TreeNode* left = pq.top(); pq.pop();
            TreeNode* right = pq.top(); pq.pop();
            TreeNode* newNode = new TreeNode('\0', left->freq + right->freq);
            newNode->left = left;
            newNode->right = right;
            pq.push(newNode);
        }

        root = pq.top();
    }
};

void buildEncodingMap(TreeNode* node, const string& str, unordered_map<char, string>& encodingMap) {
    if (!node) return;
    if (node->key != '\0') {
        encodingMap[node->key] = str;
    }
    buildEncodingMap(node->left, str + "0", encodingMap);
    buildEncodingMap(node->right, str + "1", encodingMap);
}

string encode(TreeNode* root, const string& text) {
    unordered_map<char, string> encodingMap;
    buildEncodingMap(root, "", encodingMap);

    string encoded;
    for (char ch : text) {
        encoded += encodingMap[ch];
    }

    return encoded;
}

string decode(TreeNode* root, const string& encoded) {
    string decoded;
    TreeNode* currentNode = root;
    for (char bit : encoded) {
        if (currentNode == nullptr) {
            cerr << "Error: currentNode is null." << endl;
            return "";
        }
        currentNode = (bit == '0') ? currentNode->left : currentNode->right;
        if (currentNode && !currentNode->left && !currentNode->right) {
            decoded += currentNode->key;
            currentNode = root;
        }
    }
    return decoded;
}

BST buildFrequencyBST(const string& text) {
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        if (isalnum(ch) || ch == ' ') {
            freqMap[ch]++;
        }
    }

    BST bst;
    for (const auto& pair : freqMap) {
        bst.insert(pair.first, pair.second);
    }

    return bst;
}

#endif // ENCODING_H
