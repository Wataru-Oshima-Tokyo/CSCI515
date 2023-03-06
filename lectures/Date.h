/* sample.h */

#ifndef DATE_H
#define DATE_H

class Date {
    public:
        Date();
        int year;
        int month;
        int day;
        friend std::ostream& operator<<(std::ostream& os, const Date& dt);

};

Date::Date(){}


#endif