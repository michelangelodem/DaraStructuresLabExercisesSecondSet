#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "Sorter.h"

class HeapSort: public Sorter {
    private:
        void heapify(vector<Record>& records, size_t index, size_t length);
    public:
        void sort(vector<Record>& records) override;
};

#endif 
