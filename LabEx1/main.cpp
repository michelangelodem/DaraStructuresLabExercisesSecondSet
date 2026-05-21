#include <iostream>
#include <vector>
#include <memory>
#include "../Data/Mapper.h"
#include "../Sorting/CountingSort.h"
#include "../Sorting/MergeSort.h"

using namespace std;


void displayRecordBunch(const vector<Record>& records, int start, int count) {
    cout <<  "--------------------------------------------------" <<endl;
    for (int i = start; i < start + count && i < records.size(); ++i) {
        cout << "Record " << (i + 1) << ": ";
        records[i].display();
        cout <<  "--------------------------------------------------" <<endl;
    }
}

void executeSort(Sorter& s, vector<Record>& records, Sorter::key_extractor ext) { 
    try{     
        s.setExtractor(ext);   
        s.sort(records);
    } catch (const exception& e) {
        cout << "Error during sorting: " << e.what() << endl;
        throw;
    }    
    s.isSorted(records) ? cout<< s.name << " successful\n" : 
                            cout<< s.name << " failed\n";
}

vector<Record> getRecordsFromFile(const string path) {
    vector<Record> res;
    try {
        res = Mapper::fileToRecords(path);
    } catch (const exception& e) {
        throw runtime_error("Error loading records from CSV");
    }
    if (res.empty()) {
        throw runtime_error("Error: No records loaded from CSV file.");
    }
    else {
        cout << "Successfully loaded " << res.size() << " records." << endl << endl;
    }
    return res;
}

int main() {
    try {    
        const string csvFilePath = "../effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
        vector<Record> records_for_ms = getRecordsFromFile(csvFilePath);
        vector<Record> records_for_cs = records_for_ms;

        unique_ptr<Sorter> cs = make_unique<CountingSort>();
        executeSort(*cs, records_for_cs, [](const Record& r) {return r.getCumulative(); });

        unique_ptr<Sorter> ms = make_unique<MergeSort>();
        executeSort(*ms, records_for_ms, [](const Record& r) {return r.getCumulative(); });

        cout << "After Sorting: " << endl;
        displayRecordBunch(records_for_cs, 0, 5);
        cout << endl;
        displayRecordBunch(records_for_cs, max(0, (int)records_for_cs.size() - 5), 5);
        cout << endl;
    } catch (const exception& e) {
        cerr << "\n[FATAL ERROR] Application aborted: " << e.what() << endl;
        return 1;
    }
    return 0;
}
