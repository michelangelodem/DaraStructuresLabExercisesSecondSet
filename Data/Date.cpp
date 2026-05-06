#include "Date.h"

Date::Date(int d, int m, int y) {
    if (d < 1 || d > 31 
        || m < 1 || m > 12 
        || y < 2015 || y > 2021) {
        throw std::invalid_argument("Invalid date");
    }

    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) {
        throw std::invalid_argument("Invalid date for the given month");
    }

    if (m == 2) {
        int maxDay = is_leap_year() ? 29 : 28;
        if (d > maxDay) {
            throw std::invalid_argument("Invalid date for February");
        }
    }

    day = d;
    month = m;
    year = y;
}

// Getters

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) {
        return year < other.year;
    } else if (month != other.month) {
        return month < other.month;
    } else {
        return day < other.day;
    }
}

void Date::display() const {
    printf("%02d/%02d/%04d\n", day, month, year);
}