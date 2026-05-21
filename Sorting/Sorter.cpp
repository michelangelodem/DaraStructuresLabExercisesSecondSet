#include "Sorter.h"

void Sorter::setExtractor(key_extractor ext) { this->extractor = ext; }

bool Sorter::isSorted(vector<Record>& records) const {
    for (size_t i = 1; i < records.size(); ++i) {
        if (extractor(records[i])<extractor(records[i-1])) {
            printf("Out of order: \n%lli \n %lli \n", records[i], records[i-1]);
            return false;
        }
    }
    return true;
}