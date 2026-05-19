#include <iostream>
#include <vector>
#include "../Data/Date.h"
#include "../Data/Mapper.h"
#include "../Sorting/HeapSort.h"
#include "../Sorting/QuickSort.h"
#include "../Sorting/Sorter.h"

using namespace std;

#define VALUE 1  

void displayRecordBunch(const vector<Record>& records, int start, int count) {
    cout <<  "--------------------------------------------------" <<endl;
    for (int i = start; i < start + count && i < records.size(); ++i) {
        cout << "Record " << (i + 1) << ": ";
        records[i].display();
    }
    cout <<  "--------------------------------------------------" <<endl;
}

int main() {
    const string csvFilePath = "../effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
    vector<Record> records_for_hs;
    vector<Record> records_for_qs;

    try {
        records_for_hs = Mapper::fileToRecords(csvFilePath);
        records_for_qs = records_for_hs; 
    } catch (const exception& e) {
        cerr << "Error loading records from CSV: " << e.what() << endl;
        return 1;
    }
    if (records_for_hs.empty()) {
        cerr << "Error: No records loaded from CSV file." << endl;
        return 1;
    }

    cout << "Successfully loaded " << records_for_hs.size() << " records." << endl << endl;

    HeapSort hs = HeapSort();
    QuickSort qs = QuickSort();

    try {
        hs.sort(records_for_hs);
        qs.sort(records_for_qs);
    } catch (const exception& e) {
        cerr << "Error during sorting: " << e.what() << endl;
        return 1;
    }
    cout << "After Sorting: " << endl;
    displayRecordBunch(records_for_qs, 0, 5);
    cout << endl;
    displayRecordBunch(records_for_qs, max(0, (int)records_for_qs.size() - 5), 5);
    cout << endl;

    hs.isSorted(records_for_hs, VALUE) ? printf("Heap sort successful\n") : printf("Heap sort failed\n");
    qs.isSorted(records_for_qs, VALUE) ? printf("Quick sort successful\n") : printf("Quick sort failed\n");
    return 0;
}