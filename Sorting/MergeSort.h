#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "Sorter.h"

#define CUMULATIVE 2

using namespace std;

class MergeSort: public Sorter {
    private:  
        void merge(vector<Record>& arr, int left, int mid, int right, key_extractor extractor);
        void mergeSortHelper(vector<Record>& arr, int left, int right, key_extractor extractor);
    
    public: 
        MergeSort() : Sorter("Merge sort") {}
        vector<Record> sort(vector<Record>& records, key_extractor ext) override;
    };

#endif 
