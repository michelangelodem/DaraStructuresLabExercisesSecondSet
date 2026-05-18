#include <iostream>
#include <vector>
#include "../Data/Date.h"
#include "../Data/Mapper.h"
#include "../Sorting/CountingSort.h"
#include "../Sorting/MergeSort.h"
#include "../Sorting/Sorter.h"

using namespace std;

#define CUMULATIVE 2    

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
    vector<Record> records_for_ms;
    vector<Record> records_for_cs;

    try {
        records_for_ms = Mapper::fileToRecords(csvFilePath);
        records_for_cs = records_for_ms; 
    } catch (const exception& e) {
        cerr << "Error loading records from CSV: " << e.what() << endl;
        return 1;
    }
    if (records_for_ms.empty()) {
        cerr << "Error: No records loaded from CSV file." << endl;
        return 1;
    }

    cout << "Successfully loaded " << records_for_ms.size() << " records." << endl << endl;

    MergeSort ms = MergeSort();
    CountingSort cs = CountingSort();

    try {
        ms.sort(records_for_ms);
        cs.sort(records_for_cs);
    } catch (const exception& e) {
        cerr << "Error during sorting: " << e.what() << endl;
        return 1;
    }
    cout << "After Sorting: " << endl;
    displayRecordBunch(records_for_cs, 0, 5);
    cout << endl;
    displayRecordBunch(records_for_cs, max(0, (int)records_for_cs.size() - 5), 5);
    cout << endl;

    ms.isSorted(records_for_ms, CUMULATIVE) ? printf("Merge sort successful\n") : printf("Merge sort failed\n");
    cs.isSorted(records_for_cs, CUMULATIVE) ? printf("Counting sort successful") : printf("Counting sort failed");

    return 0;
}
