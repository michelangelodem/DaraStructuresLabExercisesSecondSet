#include "QuickSort.h"

int QuickSort::hoarePartition(vector<Record>& records, int low, int high) {
    long long pivot = records[low].getValue();
    int i = low;
    int j = high;

    while (true) {
        while (records[i].getValue() < pivot) 
            i++;
        while (records[j].getValue() > pivot)
            j--;
        if (i >= j) return j;
        
        swap(records[i], records[j]);

        i ++; j--;
    }
}

void QuickSort::sortHelper(vector<Record>& records, int low, int high) {
    if (low < high) {
        int pivot = hoarePartition(records, low, high);

        sortHelper(records, low, pivot);
        sortHelper(records, pivot + 1, high);
    }
}

void QuickSort::sort(vector<Record>& records) {
    int size = records.size() - 1;
    sortHelper(records, 0, size);
}