#include "../Executor.h"

Record binarySearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
    int low = 0;
    int high = recs.size() - 1;
    while (low <= high) {
        int midVal = low + (high - low) / 2;
        long long midKey = ext(recs[midVal]);
        if (midKey == target) {
            return recs[midVal];
        } else if (midKey < target) {
            low = midVal + 1; 
        } else {
            high = midVal - 1; 
        }
    }
    return Record(); 
}

Record interoplationSearch(const vector<Record>& recs, long long target, Sorter::key_extractor ext) {
}

int main() {
    try {    
        const string csvFilePath = "../effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
        auto ms = make_unique<MergeSort>();
        auto cs = make_unique<CountingSort>();
        auto hs = make_unique<HeapSort>();
        auto qs = make_unique<QuickSort>();

        Executor executor(*ms, csvFilePath, [](const Record& r) {return r.getCumulative(); });
        executor.executeSearch(binarySearch);

        executor.setSorter(*cs);
        executor.executeSearch(binarySearch);

        executor.setSorter(*hs);
        executor.executeSearch(binarySearch);

        executor.setSorter(*qs);
        executor.executeSearch(binarySearch);

    } catch (const exception& e) {
        cerr << "\n[FATAL ERROR] Application aborted: " << e.what() << endl;
        return 1;
    }
    return 0;
}
