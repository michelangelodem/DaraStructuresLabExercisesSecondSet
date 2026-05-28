#include "../Executor.h"

int main() {
    try {    
        const string csvFilePath = "../effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
        auto ms = make_unique<MergeSort>();
        auto cs = make_unique<CountingSort>();
        auto hs = make_unique<HeapSort>();
        auto qs = make_unique<QuickSort>();

        Executor executor(*ms, csvFilePath, [](const Record& r) {return r.getCumulative(); });
        executor.executeSort();

        executor.setSorter(*cs);
        executor.executeSort();

        executor.setExtractor([](const Record& r) {return r.getValue(); });
        executor.setSorter(*hs);
        executor.executeSort();

        executor.setSorter(*qs);
        executor.executeSort();
    } catch (const exception& e) {
        cerr << "\n[FATAL ERROR] Application aborted: " << e.what() << endl;
        return 1;
    }
    return 0;
}
