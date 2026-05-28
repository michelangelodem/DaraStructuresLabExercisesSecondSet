#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <iostream>
#include <functional>
#include "../Data/Record.h"

class Sorter {
    public:    
        using key_extractor = function<long long(const Record&)>;
        const string name = "Sort";
        
        virtual vector<Record> sort(vector<Record>& records, key_extractor ext) = 0;
        bool isSorted(const vector<Record>& records, key_extractor ext) const; 
    protected:        
        Sorter(string sorterName) : name(sorterName) {}
};

#endif 