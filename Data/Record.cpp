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
    printf("\n");
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