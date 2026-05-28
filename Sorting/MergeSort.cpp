#include "MergeSort.h"

void MergeSort::merge(vector<Record>& arr, int left, int mid, int right, key_extractor extractor) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    vector<Record> leftArr(leftSize);
    vector<Record> rightArr(rightSize);

    for (int i = 0; i < leftSize; ++i) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; ++i) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0;   
    int j = 0;   
    int k = left;

    while (i < leftSize && j < rightSize) {
        if (extractor(leftArr[i]) < extractor( rightArr[j])) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    while (i < leftSize) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < rightSize) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void MergeSort::mergeSortHelper(vector<Record>& arr, int left, int right, key_extractor extractor) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid, extractor);

        mergeSortHelper(arr, mid + 1, right, extractor);

        merge(arr, left, mid, right, extractor);
    }
}

vector<Record> MergeSort::sort(vector<Record>& records, key_extractor ext) {
    if (ext == nullptr) {
        string errorMsg = "Set key extractor before sorting in: " + name + ".";
        throw std::invalid_argument(errorMsg);
    }
    if (records.empty()) {
        cout << "Warning: Empty records vector." << endl;
        return records;
    }
    mergeSortHelper(records, 0, records.size() - 1, ext);
    return records;
}