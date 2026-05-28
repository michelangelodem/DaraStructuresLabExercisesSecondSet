#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <functional>
#include "Data/Mapper.h"
#include "Sorting/MergeSort.h"
#include "Sorting/QuickSort.h"
#include "Sorting/HeapSort.h"
#include "Sorting/CountingSort.h"

using namespace std::chrono;

class Executor {
    private:
        std::reference_wrapper<Sorter> sorter;
        vector<Record> records;
        Sorter::key_extractor ext;
        
        vector<Record> getRecordsFromFile(const string path);
    public:
        using searcher = std::function<Record(const vector<Record>&, long long, Sorter::key_extractor)>;
        
        Executor(Sorter& s, const string filePath, Sorter::key_extractor extractor) : 
            sorter(s), ext(extractor) {
                records = getRecordsFromFile(filePath);
            }
        
        void executeSort();
        void executeSearch(searcher search_func);
        void setSorter(Sorter& s) { sorter = s; }
        void setExtractor(Sorter::key_extractor extractor) { this->ext = extractor; }
        void displayRecordBunch(vector<Record> records, int start, int count) const;
        ~Executor() = default;
};