#include "Sorter.h"

bool Sorter::isSorted(vector<Record>& records, size_t index) const {
    for (size_t i = 1; i < records.size(); ++i) {
        if (records[i].lessThanInRegardTo(records[i-1], index)) {
            records[i-1].display();
            records[i].display();
            return false;
        }
    }
    return true;
}