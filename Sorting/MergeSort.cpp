#include "MergeSort.h"

void MergeSort::merge(vector<Record>& arr, int left, int mid, int right) {
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

void MergeSort::mergeSortHelper(vector<Record>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid);

        mergeSortHelper(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void MergeSort::sort(vector<Record>& records) {
    if (extractor == nullptr) {
        string errorMsg = "Set key extractor before sorting in: " + name + ".";
        throw std::invalid_argument(errorMsg);
    }
    if (records.empty()) {
        cout << "Warning: Empty records vector." << endl;
        return;
    }
    if (records.empty()) {
        cout << "Warning: Empty records vector." << endl;
    }
    mergeSortHelper(records, 0, records.size() - 1);
}