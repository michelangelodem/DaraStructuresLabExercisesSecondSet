#include "../Executor.h"
#include "../Sorting/MergeSort.h"
#include "../Sorting/CountingSort.h"
#include "../Sorting/HeapSort.h"
#include "../Sorting/QuickSort.h"
#include "Search.h"

int main() {
    try {    
        const string csvFilePath = "../effects-of-covid-19-on-trade-at-15-december-2021-provisional.csv";
        auto ms = make_shared<MergeSort>();
        auto cs = make_shared<CountingSort>();
        auto hs = make_shared<HeapSort>();
        auto qs = make_shared<QuickSort>();

        Executor executor(ms, csvFilePath, [](const Record& r) {return r.getCumulative(); });
        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);

        executor.setSorter(cs);
        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);
        executor.executeSearch(bisStarSearch);

        executor.setSorter(hs);
        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);

        executor.setSorter(qs);
        executor.executeSearch(binarySearch);
        executor.executeSearch(interoplationSearch);
        executor.executeSearch(binaryInterpolationSearch);

    } catch (const exception& e) {
        cerr << "\n[FATAL ERROR] Application aborted: " << e.what() << endl;
        return 1;
    }
    return 0;
}
