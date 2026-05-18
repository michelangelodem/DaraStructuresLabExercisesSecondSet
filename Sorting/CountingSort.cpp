#include "CountingSort.h"

void CountingSort::sort(vector<Record>& records) {
    if (records.empty()) {
        cout << "Warning: Empty records vector." << endl;
        return;
    }

    long long maxValue = records[0].getCumulative()/1000; // Scale down to handle large values;
    if (maxValue < 0) {
            printf("Error: In ");
            records[0].display();
            printf(" - ");
            printf("Negative value encountered: %lld\n", maxValue);
        throw invalid_argument("CountingSort cannot handle negative values for the selected field.");
    }

    if (maxValue > SIZE_MAX) {
        printf("Error: In ");
        records[0].display();
        printf(" - ");
        printf("Value exceeds maximum allowed size: %lld\n", maxValue);
        throw invalid_argument("CountingSort cannot handle values that exceed the maximum allowed size.");
    }

    for (const Record& record : records) {
        long long value = record.getCumulative()/1000; // Scale down to handle large values
        if (value < 0) {
            printf("Error: In ");
            record.display();
            printf(" - ");
            printf("Negative value encountered: %lld\n", value);
            throw invalid_argument("CountingSort cannot handle negative values for the selected field.");
        }
    if (value > SIZE_MAX) {
        printf("Error: In ");
        record.display();
        printf(" - ");
        printf("Value exceeds maximum allowed size: %lld\n", value);
        throw invalid_argument("CountingSort cannot handle values that exceed the maximum allowed size.");
    }        
        if (value > maxValue) {
            maxValue = value;
        }
    }

    vector<long long> count(static_cast<size_t>(maxValue) + 1, 0);
    for (const Record& record : records) {
        long long value = record.getCumulative()/1000; // Scale down to handle large values
        count[value]++;
    }

    for (long long i = 1; i <= maxValue; ++i) {
        count[i] += count[i - 1];
    }

    vector<Record> output(records.size());
    for (long long i = records.size() - 1; i >= 0; --i) {
        long long value = records[i].getCumulative()/1000;
        output[count[value] - 1] = records[i];
        count[value]--;
    }

    for (size_t i = 0; i < records.size(); ++i) {
        records[i] = output[i];
    }
}