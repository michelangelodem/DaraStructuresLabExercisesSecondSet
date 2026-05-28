#include "Sorter.h"

bool Sorter::isSorted(const vector<Record>& records, key_extractor ext) const {
    for (size_t i = 1; i < records.size(); ++i) {
        if (ext(records[i]) < ext(records[i-1])) {
            printf("Out of order: \n%lli \n %lli \n", ext(records[i]), ext(records[i-1]));
            return false;
        }
    }
    return true;
}