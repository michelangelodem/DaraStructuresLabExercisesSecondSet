#include "Record.h"

Record::Record(const Date& d, long long v, long long c) {
    date = d;
    value = v;
    cumulative = c;
}

const Date Record::getDate() const {
    return date;
}

long long Record::getValue() const {
    return value;
}

long long Record::getCumulative() const {
    return cumulative;
}

void Record::display() const {
    printf("\nDate: ");
    date.display();
    printf("Value: %lld, \nCumulative: %lld\n", value, cumulative);
}

bool Record::lessThanInRegardTo(const Record& other, size_t index) const {
    if (index == 0) {
        return date < other.date;
    } else if (index == 1) {
        return value < other.value;
    } else if (index == 2) {
        return cumulative < other.cumulative;
    } else {
        throw std::invalid_argument("Invalid index for comparison. Must be 0, 1, or 2.");
    }
}

long long Record::getValueAtIndex(size_t index) const {
    if (index == 0) {
        throw std::invalid_argument("Cannot retrieve Date as an integer value. Use index 1 (Value) or 2 (Cumulative).");
    } else if (index == 1) {
        return value;
    } else if (index == 2) {
        return cumulative;
    } else {
        throw std::invalid_argument("Invalid index for value retrieval. Must be 0, 1, or 2.");
    }
}