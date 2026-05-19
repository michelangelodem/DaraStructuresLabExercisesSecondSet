#ifndef SORTER_H
#define SORTER_H

#include "../Data/Record.h"
#include <vector>
#include <iostream>

using namespace std;

class Sorter {
    protected:
        virtual void sort(vector<Record>& records) = 0;
    public:    
        bool isSorted(vector<Record>& records, size_t index) const; 
};

#endif 