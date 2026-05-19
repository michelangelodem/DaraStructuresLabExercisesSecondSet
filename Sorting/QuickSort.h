#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "Sorter.h"

class QuickSort: public Sorter {
    private:
        int hoarePartition(vector<Record>& records, int low, int high);
        void sortHelper(vector<Record>& records, int low, int high);
    public:
        void sort(vector<Record>& records) override;
};

#endif 