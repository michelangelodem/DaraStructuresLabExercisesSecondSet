#include "hashTable.h"
#include <iostream>

using namespace std;

hashNode::hashNode(const Record& r) : data(r), next(nullptr) {}

HashTable::HashTable() : size(1013) {
    buckets.resize(size, nullptr);
}

int HashTable::hashFunction(const Date& date) {
    int key = date.getYear() * 10000 + date.getMonth() * 100 + date.getDay();
    return key % size;
}

void HashTable::insert(const Record& r) {
    int index = hashFunction(r.getDate());
    hashNode* newNode = new hashNode(r);
    
    if (buckets[index] == nullptr) {
        buckets[index] = newNode;
    } else {
        newNode->next = buckets[index];
        buckets[index] = newNode;
    }
}

void HashTable::search(const Date& date) {
    int index = hashFunction(date);
    hashNode* current = buckets[index];
    
    while (current != nullptr) {
        if (current->data.getDate() == date) {
            current->data.display();
        }
        current = current->next;
    }
}

void HashTable::update(const Date& date, long long newCml) {
    int index = hashFunction(date);
    hashNode* current = buckets[index];
    
    while (current != nullptr) {
        if (current->data.getDate() == date) {
            cout << "Record updated." << endl;
            current->data.setCumulative(newCml);
        }
        current = current->next;
    }
}

void HashTable::deleteN(const Date& date) {
    int index = hashFunction(date);
    hashNode* current = buckets[index];
    hashNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->data.getDate() == date) {
            if (prev == nullptr) {
                buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Record deleted." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Record not found." << endl;
}
