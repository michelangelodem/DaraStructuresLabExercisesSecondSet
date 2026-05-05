#ifndef SORTER_H
#define SORTER_H

#include "../Data/Record.h"
#include <vector>
#include <iostream>

using namespace std;

class Sorter {
    protected:
        size_t sorting_index;

        void displaySortingIndexInfo();
    public:
        Sorter() : sorting_index(0) {}

        virtual void sort(vector<Record>& records) = 0;

        void displayRecords(const std::vector<Record>& records);

        bool isSortedInRegardTo(const std::vector<Record>& records);

        virtual void setIndex(size_t idx);

        virtual ~Sorter() {};
};

#endif 