#include "Sorter.h"

void Sorter::displayRecords(const vector<Record>& records) {
    cout << "\n========== Records (Sorted) ==========" << endl;
    for (const auto& record : records) {
        record.display();
    }
}

bool Sorter::isSortedInRegardTo(const vector<Record>& records) {
    for (size_t i = 0; i < records.size() - 1; ++i) {
        if (records[i + 1].lessThanInRegardTo(records[i], this->sorting_index)) {
            return false;
        }
    }
    return true;
}

void Sorter::displaySortingIndexInfo() {
    if (this->sorting_index == 0) {
        cout << "Sorting by Date..." << endl;
    } else if (this->sorting_index == 1) {
        cout << "Sorting by Value..." << endl;
    } else if (this->sorting_index == 2) {
        cout << "Sorting by Cumulative..." << endl;
    } else {
        cout << "Invalid sorting index. Defaulting to Date." << endl;
    }
}

void Sorter::setIndex(size_t idx) {
    if (idx < 0 || idx > 2) {
            throw invalid_argument("Invalid index for sorting. Must be 0 (Date), 1 (Value), or 2 (Cumulative).");
    }
    this->sorting_index = idx;
    this->displaySortingIndexInfo();
}