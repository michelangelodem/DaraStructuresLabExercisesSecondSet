#include "HeapSort.h"

void HeapSort::heapify(vector<Record>& records, size_t root_idx, size_t length, key_extractor extractor) {
    size_t largest = root_idx; 
    size_t left = 2*root_idx + 1; 
    size_t right = 2*root_idx +2; 

    if ((left < length)&&(extractor(records[left]) > extractor(records[largest])))
        largest = left;
    
    if ((right < length)&&(extractor(records[right]) > extractor(records[largest])))
        largest = right;

    if (largest != root_idx) {
        swap(records[root_idx], records[largest]);
        heapify(records, largest, length, extractor);
    }
}

vector<Record> HeapSort::sort(vector<Record>& records, key_extractor ext) {
    if (ext == nullptr) {
        string errorMsg = "Set key extractor before sorting in: " + name + ".";
        throw std::invalid_argument(errorMsg);
    }
    if (records.empty()) {
        cout << "Warning: Empty records vector." << endl;
        return records;
    }
    for (int i = records.size()/2 - 1; i >= 0; i--)
        heapify(records, i, records.size(), ext);

    for (int i = records.size() -1; i>0; i--) {
        swap(records[0], records[i]);
        heapify(records, 0, i, ext);
    }
    return records;
}