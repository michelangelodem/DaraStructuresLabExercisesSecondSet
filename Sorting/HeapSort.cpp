#include "HeapSort.h"

void HeapSort::heapify(vector<Record>& records, size_t root_idx, size_t length) {
    size_t largest = root_idx; 
    size_t left = 2*root_idx + 1; 
    size_t right = 2*root_idx +2; 

    if ((left < length)&&(records[left].getValue() > records[largest].getValue()))
        largest = left;
    
    if ((right < length)&&(records[right].getValue() > records[largest].getValue()))
        largest = right;

    if (largest != root_idx) {
        swap(records[root_idx], records[largest]);
        heapify(records, largest, length);
    }
}

void HeapSort::sort(vector<Record>& records){
    for (int i = records.size()/2 - 1; i >= 0; i--)
        heapify(records, i, records.size());    

    for (int i = records.size() -1; i>0; i--) {
        swap(records[0], records[i]);
        heapify(records, 0, i);
    }
}