#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "Sorter.h"

using namespace std;

class MergeSort : public Sorter {
    private:
        void merge(vector<Record>& arr, int left, int mid, int right);

        void mergeSortHelper(vector<Record>& arr, int left, int right);

    public:
        void sort(vector<Record>& records);
    };

#endif 
