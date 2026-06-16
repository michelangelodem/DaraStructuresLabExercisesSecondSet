#include "Executor.h"

void Executor::executeSort() {
    vector<Record> recs = records;
    try {
        //Executor::displayRecordBunch(recs, 0, 5);
        auto start = high_resolution_clock::now();
        recs = sorter.get().sort(recs, ext);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        //Executor::displayRecordBunch(recs, recs.size() - 5, 5);
        cout << "Time taken by " << sorter.get().name << ": " << duration.count() << " ms" << endl;
    } catch (const exception& e) {
        cout << "Error during sorting: " << e.what() << endl;
        throw;
    }    
    sorter.get().isSorted(recs, ext) ? cout<< sorter.get().name << " successful\n" : 
                            cout<< sorter.get().name << " failed\n";
}

void Executor::executeSearch(searcher search_func) {
    vector<Record> recs = records;
    try {
        recs = sorter.get().sort(recs, ext);
        cout << "Give a key to search for: ";
        long long key;
        cin >> key;
        auto start = high_resolution_clock::now();
        Record found = search_func(recs, key, ext);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Time taken in: " << sorter.get().name << " sorted records is: " << duration.count() << " μs" << endl;
        found.display();
    } catch (const exception& e) {
        cout << "Error during searching: " << e.what() << endl;
        throw;
    }
}

vector<Record> Executor::getRecordsFromFile(const string path) {
    vector<Record> res;
    try {
        res = Mapper::fileToRecords(path);
    } catch (const exception& e) {
        throw runtime_error("Error loading records from CSV: " + string(e.what()));
    }
    if (res.empty()) {
        throw runtime_error("Error: No records loaded from CSV file.");
    }
    else {
        cout << "Successfully loaded " << res.size() << " records." << endl << endl;
    }
    return res;
}

void Executor::displayRecordBunch(vector<Record> records, int start, int count) const {
    cout <<  "--------------------------------------------------" <<endl;
    for (int i = start; i < start + count && i < records.size(); ++i) {
        cout << "Record " << (i + 1) << ": ";
        records[i].display();
        cout <<  "--------------------------------------------------" <<endl;
    }
}