#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include "Sorter.h"

class CountingSort: public Sorter {
    private:
        long long setMaxValue(vector<Record>& records);
        vector<long long> getFrequencyArr(vector<Record>& records, long long maxValue);
    public:
        void sort(vector<Record>& records) override;
};

#endif 