//
// Created by Waosb on 03/02/2024.
//

#ifndef INC_376EVENTS_DATE_H
#define INC_376EVENTS_DATE_H

#include <QDate>
#include <string>

class Date {

private:
    std::string month;
    int day;
    int year; //a four digit number.

public:
    Date();

    Date(std::string monthString, int day, int year);

    Date(int monthInt, int day, int year);

    Date(int year);

    Date(std::string strDate);

    Date(Date const &aDate);

    void setDate(int monthInt, int day, int year);

    void setDate(const std::string& monthString, int day, int year);

    void setDate(int year);

    void setYear(int year);

    void setMonth(int monthNumber);

    void setDay(int day);

    int getMonth();

    int getDay();

    int getYear();

    std::string toString();

    bool equals(const Date& otherDate);

    bool precedes(Date otherDate);

    QDate convertDate();

private:
    bool dateOK(int monthInt, int dayInt, int yearInt);

    bool dateOK(std::string monthString, int dayInt, int yearInt);

    static bool monthOK(const std::string& month);

    static std::string monthString(int monthNumber);
};

#endif //INC_376EVENTS_DATE_H
