#include "CountingSort.h"

void CountingSort::sort(vector<Record>& records) {
    if (extractor == nullptr) {
        string errorMsg = "Set key extractor before sorting in: " + name + ".";
        throw std::invalid_argument(errorMsg);
    }
    if (records.empty()) {
        cout << "Warning: Empty records vector." << endl;
        return;
    }
    
    long long maxValue = setMaxValue(records);
    vector<long long> count = getFrequencyArr(records, maxValue);
    vector<Record> output(records.size());
    
    long long value = 0;
    long long position = 0;

    for (long long i = records.size() - 1; i >= 0; --i) {
        value = extractor(records[i])/1000;
        position = count[value] -1;
        output[position] = records[i];
        count[value]--;
    }
    
    for (size_t i = 0; i < records.size(); ++i) {
        records[i] = output[i];
    }
}

long long CountingSort::setMaxValue(vector<Record>& records) {
    long long maxValue = extractor(records[0]) / 1000;
    if ((maxValue < 0)||(maxValue > SIZE_MAX)) 
        throw invalid_argument("Invalid value at records index 0");
    
    long long value = 0;
    for (const auto& record : records) {
        value = extractor(record)/ 1000;
        if ((value < 0)||(value > SIZE_MAX)) 
            throw invalid_argument("Invalid value while determining max value");
        
        if (value > maxValue)
            maxValue = value;
    }

    return maxValue;
}

vector<long long> CountingSort::getFrequencyArr(vector<Record>& records, long long maxValue) {
    vector<long long> count(static_cast<size_t>(maxValue) + 1, 0);
    //count:
    long long value = 0;
    for (const auto& record : records) {
        value = extractor(record)/ 1000;
        count[value]++;
    }

    //add the previous:
    for (long long i = 1; i <= maxValue; ++i) {
        count[i] += count[i-1];
    }
    return count;
}