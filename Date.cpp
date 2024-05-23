//
// Created by Waosb on 03/02/2024.
//
#include "Date.h"

#include <iostream>
#include <vector>
using namespace std;

Date::Date() {
        month = "January";
        day = 1;
        year = 1000;
    }

Date::Date(string monthString, int day, int year)
    {
        setDate(monthString, day, year);
    }

Date::Date(int monthInt, int day, int year)
    {
        setDate(monthInt, day, year);
    }

Date::Date(int year)
    {
        setDate(1, 1, year);
    }

    //@Deprecated
    Date::Date(string strDate)
    {
        int monthInt = 1;
        int dayInt = 1;
        int yearInt = 1;

        string delimiter = "/";
        size_t pos_start = 0, pos_end, delim_len = 1;
        std::string token;
        vector<std::string> monDayYear;
        while ((pos_end = strDate.find(delimiter, pos_start)) != std::string::npos) {
            token = strDate.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            monDayYear.push_back (token);
        }

        monDayYear.push_back (strDate.substr (pos_start));
        if(!monDayYear[0].empty())
        {

            monthInt = stoi(monDayYear[0]);
            dayInt = stoi(monDayYear[1]);
            yearInt = stoi(monDayYear[2]);
        }
        setDate(monthInt, dayInt, yearInt);
    }

    //copy constructor
    Date::Date(Date const &aDate)
    {
        month = aDate.month;
        day = aDate.day;
        year = aDate.year;
    }

void Date::setDate(int monthInt, int dayInt, int yearInt)
    {
        if (dateOK(monthInt, dayInt, yearInt))
        {
            month = monthString(monthInt);
            day = dayInt;
            year = yearInt;
        }
        else
        {
            month = monthString(monthInt);
            day = 1;
            year = 1;
        }
    }


void Date::setDate(const string& monthString, int dayInt, int yearInt)
    {
        if (dateOK(monthString, dayInt, yearInt))
        {
            month = monthString;
            day = dayInt;
            year = yearInt;
        }
        else
        {
            cerr << "Fatal Error setDate" << endl;
            exit(0);
        }
    }

void Date::setDate(int yearInt)
    {
        setDate(1, 1, yearInt);
    }

void Date::setYear(int yearInt)
    {
        if ( (year < 1000) || (year > 9999) )
        {
            cerr << "Fatal Error setYear" << endl;
            exit(0);
        }
        else
            year = yearInt;
    }
void Date::setMonth(int monthNumber)
    {
        if ((monthNumber <= 0) || (monthNumber > 12))
        {
            cerr << "Fatal Error setMonth" << endl;
            exit(0);
        }
        else
            month = monthString(monthNumber);
    }

void Date::setDay(int dayInt)
    {
        if ((day <= 0) || (day > 31))
        {
            cerr << "Fatal Error setDay" << endl;
            exit(0);
        }
        else
            day = dayInt;
    }

int Date::getMonth( )
    {
        if (month == "January")
            return 1;
        else if (month == "February")
            return 2;
        else if (month == "March")
            return 3;
        else if (month == "April")
            return 4;
        else if (month == "May")
            return 5;
        else if (month == "June")
            return 6;
        else if (month == "July")
            return 7;
        else if (month == "August")
            return 8;
        else if (month == "September")
            return 9;
        else if (month == "October")
            return 10;
        else if (month == "November")
            return 11;
        else if (month == "December")
            return 12;
        else
        {
            cerr << "Fatal Error getMonth" << endl;
            exit(0);
            return 0; //Needed to keep the compiler happy
        }
    }

int Date::getDay( )
    {
        return day;
    }

int Date::getYear( )
    {
        return year;
    }

string Date::toString( )
    {
        return (month + " " + to_string(day) + ", " + to_string(year));
    }

bool Date::equals(const Date& otherDate)
    {
        return ( (month == otherDate.month)
                 && (day == otherDate.day) && (year == otherDate.year) );
    }

bool Date::precedes(Date otherDate)
    {
        return ( (year < otherDate.year) ||
                 (year == otherDate.year && getMonth( ) < otherDate.getMonth( )) ||
                 (year == otherDate.year && month == otherDate.month
                  && day < otherDate.day) );
    }

QDate Date::convertDate() {
    return QDate(year, this->getMonth(), day);
}


bool Date::dateOK(int monthInt, int dayInt, int yearInt)
    {
        return ( (monthInt >= 1) && (monthInt <= 12) &&
                 (dayInt >= 1) && (dayInt <= 31) &&
                 (yearInt >= 1000) && (yearInt <= 9999) );
    }

bool Date::dateOK(string monthString, int dayInt, int yearInt)
    {
        return ( monthOK(monthString) &&
                 (dayInt >= 1) && (dayInt <= 31) &&
                 (yearInt >= 1000) && (yearInt <= 9999) );
    }

    bool Date::monthOK(const string& month)
    {
        return (month == "January" || month == "February" ||
                month == "March" || month == "April" ||
                month == "May" || month == "June" ||
                month == "July" || month == "August" ||
                month == "September" || month == "October" ||
                month == "November" || month == "December" );
    }

string Date::monthString(int monthNumber)
    {
        switch (monthNumber)
        {
            case 1:
                return "January";
            case 2:
                return "February";
            case 3:
                return "March";
            case 4:
                return "April";
            case 5:
                return "May";
            case 6:
                return "June";
            case 7:
                return "July";
            case 8:
                return "August";
            case 9:
                return "September";
            case 10:
                return "October";
            case 11:
                return "November";
            case 12:
                return "December";
            default:
                cerr << "Fatal Error" << endl;
                exit(0);
                return "Error"; //to keep the compiler happy
        }
    }
