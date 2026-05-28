#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "Sorter.h"

class QuickSort: public Sorter {
    private:
        int hoarePartition(vector<Record>& records, int low, int high, key_extractor extractor);
        void sortHelper(vector<Record>& records, int low, int high, key_extractor extractor);
    public:
        QuickSort() : Sorter("Quick sort") {}
        vector<Record> sort(vector<Record>& records, key_extractor ext) override;
};

#endif 