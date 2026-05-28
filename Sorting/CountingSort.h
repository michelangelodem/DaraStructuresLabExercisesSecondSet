#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include "Sorter.h"

class CountingSort: public Sorter {
    private:
        long long setMaxValue(vector<Record>& records, key_extractor extractor);
        vector<long long> getFrequencyArr(vector<Record>& records, long long maxValue, key_extractor extractor);
    public:
        CountingSort() : Sorter("Counting sort") {} 
        vector<Record> sort(vector<Record>& records, key_extractor ext) override;
};

#endif 