#include "BST.h"
#include <iostream>

using namespace std;

Node::Node(const Record& r) : data(r), left(nullptr), right(nullptr) {}

BST::BST() : root(nullptr) {}

Node* BST::insertHelper(Node* currentNode, const Record& r) {
    if (currentNode == nullptr) {
        return new Node(r);
    }
    
    if (r.getDate() < currentNode->data.getDate()) {
        currentNode->left = insertHelper(currentNode->left, r);
    } else {
        currentNode->right = insertHelper(currentNode->right, r);
    }
    return currentNode;
}

void BST::insert(const Record& r) {
    root = insertHelper(root, r);
}

void BST::inOrderHelper(Node* currentNode) {
    if (currentNode == nullptr) return;
    
    inOrderHelper(currentNode->left);
    currentNode->data.display();
    inOrderHelper(currentNode->right);
}

void BST::inOrder() {
    inOrderHelper(root);
}

void BST::searchHelper(Node* currentNode, const Date& dateKey) {
    if (currentNode == nullptr) {
        cout << "Date not found." << endl;
        return;
    }
    
    if (dateKey < currentNode->data.getDate()) {
        searchHelper(currentNode->left, dateKey);
    } else if (currentNode->data.getDate() < dateKey) {
        searchHelper(currentNode->right, dateKey);
    } else {
        cout << "Found record:" << endl;
        currentNode->data.display();
    }
}

void BST::search(const Date& dateKey) {
    searchHelper(root, dateKey);
}

void BST::updateHelper(Node* currentNode, const Date& dateKey, long long newValue) {
    if (currentNode == nullptr) {
        cout << "Date not found." << endl;
        return;
    }
    
    if (dateKey < currentNode->data.getDate()) {
        updateHelper(currentNode->left, dateKey, newValue);
    } else if (currentNode->data.getDate() < dateKey) {
        updateHelper(currentNode->right, dateKey, newValue);
    } else {
        cout << "Record updated." << endl;
    }
}

void BST::update(const Date& dateKey, long long newCml) {
    updateHelper(root, dateKey, newCml);
}

Node* BST::deleteNodeHelper(Node* currentNode, const Date& dateKey) {
    if (currentNode == nullptr) return nullptr;
    
    if (dateKey < currentNode->data.getDate()) {
        currentNode->left = deleteNodeHelper(currentNode->left, dateKey);
    } else if (currentNode->data.getDate() < dateKey) {
        currentNode->right = deleteNodeHelper(currentNode->right, dateKey);
    } else {
        if (currentNode->left == nullptr) {
            Node* temp = currentNode->right;
            delete currentNode;
            return temp;
        } else if (currentNode->right == nullptr) {
            Node* temp = currentNode->left;
            delete currentNode;
            return temp;
        }
        
        Node* temp = currentNode->right;
        while (temp->left != nullptr) temp = temp->left;
        currentNode->data = temp->data;
        currentNode->right = deleteNodeHelper(currentNode->right, temp->data.getDate());
    }
    return currentNode;
}

void BST::deleteNode(const Date& dateKey) {
    root = deleteNodeHelper(root, dateKey);
}

BST_cml::BST_cml() : root(nullptr) {}

Node* BST_cml::insertHelper(Node* currentNode, const Record& r) {
    if (currentNode == nullptr) {
        return new Node(r);
    }
    
    if (r.getCumulative() < currentNode->data.getCumulative()) {
        currentNode->left = insertHelper(currentNode->left, r);
    } else {
        currentNode->right = insertHelper(currentNode->right, r);
    }
    return currentNode;
}

void BST_cml::insert(const Record& r) {
    root = insertHelper(root, r);
}

Node* BST_cml::findMinHelper(Node* currentNode) {
    if (currentNode->left == nullptr) return currentNode;
    return findMinHelper(currentNode->left);
}

Node* BST_cml::findMaxHelper(Node* currentNode) {
    if (currentNode->right == nullptr) return currentNode;
    return findMaxHelper(currentNode->right);
}

void BST_cml::findMin() {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    Node* minNode = findMinHelper(root);
    cout << "Record with smallest cumulative value:" << endl;
    minNode->data.display();
}

void BST_cml::findMax() {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    Node* maxNode = findMaxHelper(root);
    cout << "Record with greatest cumulative value:" << endl;
    maxNode->data.display();
}
