#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <functional>
#include "Data/Mapper.h"
#include "Sorting/Sorter.h"

using namespace std::chrono;

class Executor {
    private:
        std::shared_ptr<Sorter> sorter;
        vector<Record> records;
        Sorter::key_extractor ext;
        
        vector<Record> getRecordsFromFile(const string path);
    public:
        using searcher = std::function<Record(const vector<Record>&, long long, Sorter::key_extractor)>;
        
        Executor(std::shared_ptr<Sorter> s, const string filePath, Sorter::key_extractor extractor) : 
            sorter(s), ext(extractor) {
                records = getRecordsFromFile(filePath);
            }
        
        void executeSort();
        void executeSearch(searcher search_func);
        void setSorter(std::shared_ptr<Sorter> s) { sorter = s; }
        void setExtractor(Sorter::key_extractor extractor) { this->ext = extractor; }
        void displayRecordBunch(vector<Record> records, int start, int count) const;
        ~Executor() = default;
};

#endif