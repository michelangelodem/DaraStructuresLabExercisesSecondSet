#ifndef RECORD_H
#define RECORD_H

#include "Date.h"
#include <iostream>

using namespace std;

class Record {
    private:
        Date date;
        long long value;
        long long cumulative;

    public:
        Record() : date(), value(0), cumulative(0) {}

        Record(const Date& d, long long v, long long c);

        void display() const;

        const Date getDate() const;

        long long getValue() const;

        long long getCumulative() const;

        bool lessThanInRegardTo(const Record& other, size_t index) const;
};

#endif