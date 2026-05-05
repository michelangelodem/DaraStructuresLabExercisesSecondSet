#include <iostream>
#include <vector>
#include "../Data/Date.h"
#include "../Data/Mapper.h"
#include "../Sorting/CountingSort.h"
#include "../Sorting/MergeSort.h"
#include "../Sorting/Sorter.h"

using namespace std;

void displayRecordBunch(const vector<Record>& records, int start, int count) {
    for (int i = start; i < start + count && i < records.size(); ++i) {
        cout << "Record " << (i + 1) << ": ";
        records[i].display();
    }
    cout << endl;
}

int main() {
    const string csvFilePath = "../effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
    vector<Record> records_for_ms;
    vector<Record> records_for_cs;

    // index 0 = date, 1 = value, 2 = cumulative
    int sortIndex = 2;
    try {
        records_for_ms = Mapper::fileToRecords(csvFilePath);
        records_for_cs = records_for_ms; // Create a copy for Counting Sort
    } catch (const exception& e) {
        cerr << "Error loading records from CSV: " << e.what() << endl;
        return 1;
    }
    if (records_for_ms.empty()) {
        cerr << "Error: No records loaded from CSV file." << endl;
        return 1;
    }

    cout << "Successfully loaded " << records_for_ms.size() << " records." << endl << endl;

    MergeSort ms;
    CountingSort cs;
    try {
        ms.setIndex(sortIndex);
        cs.setIndex(sortIndex);
    } catch (const exception& e) {
        cerr << "Error initializing Sorters: " << e.what() << endl;
        return 1;
    }
    try {
        cout << "Step 2: Last 5 records BEFORE sorting:" << endl;
        displayRecordBunch(records_for_ms, max(0, (int)records_for_ms.size() - 5), 5);
        cout << "Step 3: Applying Merge Sort algorithm..." << endl;
        ms.sort(records_for_ms);
        cout << "Step 4: Applying Counting Sort algorithm..." << endl;
        cs.sort(records_for_cs);
    } catch (const exception& e) {
        cerr << "Error during sorting: " << e.what() << endl;
        return 1;
    }

    bool sorted = ms.isSortedInRegardTo(records_for_ms);
    cout << "\nValidation: Records are " << (sorted ? "correctly sorted!" : "NOT sorted!") << " from Merge Sort" << endl << endl;
    sorted = cs.isSortedInRegardTo(records_for_cs);
    cout << "Validation: Records are " << (sorted ? "correctly sorted!" : "NOT sorted!") << " from Counting Sort" << endl << endl;

    cout << "Step 5: First 5 records AFTER sorting:" << endl;
    displayRecordBunch(records_for_cs, 0, 5);
    cout << endl;

    cout << "Step 6: Last 5 records AFTER sorting:" << endl;
    displayRecordBunch(records_for_cs, max(0, (int)records_for_cs.size() - 5), 5);
    cout << endl;

    return 0;
}
