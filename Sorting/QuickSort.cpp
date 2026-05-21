#include "QuickSort.h"

int QuickSort::hoarePartition(vector<Record>& records, int low, int high) {
    long long pivot = extractor(records[low]);
    int i = low;
    int j = high;

    while (true) {
        while (extractor(records[i]) < pivot) 
            i++;
        while (extractor(records[j]) > pivot)
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
    if (extractor == nullptr) {
        string errorMsg = "Set key extractor before sorting in: " + name + ".";
        throw std::invalid_argument(errorMsg);
    }
    if (records.empty()) {
        cout << "Warning: Empty records vector." << endl;
        return;
    }
    int size = records.size() - 1;
    sortHelper(records, 0, size);
}