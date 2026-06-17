#pragma once
#include "../Data/Record.h"
#include "../Data/Date.h"

struct Node
{
    Record data;
    Node* left;
    Node* right;

    Node(const Record& r);
};

class BST
{
private:
    Node* root;

    Node* insertHelper(Node* currentNode, const Record& r);
    void inOrderHelper(Node* currentNode);
    void searchHelper(Node* currentNode, const Date& dateKey);
    void updateHelper(Node* currentNode, const Date& dateKey, long long newValue);
    Node* deleteNodeHelper(Node* currentNode, const Date& dateKey);

public:
    void insert(const Record& r);
    void inOrder();
    void search(const Date& dateKey);
    void update(const Date& dateKey, long long newCml);
    void deleteNode(const Date& dateKey);
    BST();
};

class BST_cml
{
private:
    Node* root;
    Node* insertHelper(Node* currentNode, const Record& r);
    Node* findMinHelper(Node* currentNode);
    Node* findMaxHelper(Node* currentNode);
    void printNodesWithValue(Node* currentNode, long long cumulative);

public:
    BST_cml();
    void insert(const Record& r);
    void findMin();
    void findMax();
};