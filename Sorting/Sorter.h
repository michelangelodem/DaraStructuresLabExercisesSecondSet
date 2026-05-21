#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <iostream>
#include <functional>
#include "../Data/Record.h"

using namespace std;

class Sorter {
    public:    
        using key_extractor = function<long long(const Record&)>;
        const string name = "Sort";
        
        virtual void sort(vector<Record>& records) = 0;
        void setExtractor(key_extractor ext);
        bool isSorted(vector<Record>& records) const; 
    protected:
        key_extractor extractor = nullptr;
        
        Sorter(string sorterName) : name(sorterName) {}
};

#endif 