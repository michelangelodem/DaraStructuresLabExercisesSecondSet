#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include "Sorter.h"

class CountingSort : public Sorter {
    public:
        void sort(vector<Record>& records);
        void setIndex(size_t index) override;
};

#endif 