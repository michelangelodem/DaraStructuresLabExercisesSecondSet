#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "Sorter.h"

class HeapSort: public Sorter {
    private: 
        void heapify(vector<Record>& records, size_t index, size_t length, key_extractor extractor);
    public:
        HeapSort() : Sorter("Heap sort") {}
        vector<Record> sort(vector<Record>& records, key_extractor ext) override;
};

#endif 
