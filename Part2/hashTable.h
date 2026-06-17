#pragma once
#include "../Data/Record.h"
#include "../Data/Date.h"
#include <vector>

using namespace std;

struct hashNode
{
    Record data;
    hashNode* next;
    hashNode(const Record& r);
};

class HashTable
{
private:
    vector<hashNode*> buckets;
    int size;
    int hashFunction(const Date& date);

public:
    HashTable();
    void insert(const Record& r);
    void search(const Date& date);
    void update(const Date& date, long long newCml);
    void deleteN(const Date& date);
};