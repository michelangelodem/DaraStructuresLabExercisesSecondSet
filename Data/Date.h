#ifndef DATE_H
#define DATE_H

#include <stdexcept>

class Date {
    private:
        int day;
        int month;
        int year;
        bool is_leap_year() const {
            return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        }

    public:
        Date() : day(1), month(1), year(2015) {}

        Date(int d, int m, int y);

        int getDay() const;

        int getMonth() const;

        int getYear() const;

        bool operator<(const Date& other) const;

        void display() const;

        friend void swap(Date& d1, Date& d2);
};

#endif 