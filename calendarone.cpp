#include <iostream>
#include <QVariant>
#include <QDate>
#include <QDebug>
#include <Date.h>

class Calendar {

public:
    // Function to check if a given year is a leap year
    static bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Function to calculate the number of days in a given month and year
    static int daysInMonth(int month, int year) {
        if (month == 2) {
            return isLeapYear(year) ? 29 : 28; // February has 29 days in leap years
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        } else {
            return 31;
        }
    }

    // Function to print the calendar for a given month and year
    static void printCalendar(int month, int year) {
        std::cout << "   ----- " << month << "/" << year << " -----\n";
        std::cout << "Sun Mon Tue Wed Thu Fri Sat\n";

        // Calculate the starting day of the month
        int startDay = dayOfWeek(1, month, year);

        // Print spaces for the days before the first day of the month
        for (int i = 1; i < startDay; ++i) {
            std::cout << "    ";
        }

        // Print the days of the month
        for (int day = 1; day <= daysInMonth(month, year); ++day) {
            printf("%3d ", day);
            // Move to the next line after Saturday
            if (++startDay > 7) {
                startDay = 1;
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    // Function to calculate the day of the week for a given date
    static int dayOfWeek(int day, int month, int year) {
        if (month < 3) {
            month += 12;
            year--;
        }
        int h = (day + 13 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;

        //Added this as Saturday turned to 0 from % 7 when it is needed as 7
        h += 7 * (h == 0);

        return h;
    }

    // Function to get the current date
    static void getCurrentDate(int &day, int &month, int &year) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        day = ltm->tm_mday;
        month = 1 + ltm->tm_mon;
        year = 1900 + ltm->tm_year;
    }

    static Date getCurrentDate() {

        time_t now = time(0);
        tm *ltm = localtime(&now);
        int day = ltm->tm_mday;
        int month = 1 + ltm->tm_mon;
        int year = 1900 + ltm->tm_year;

        return Date(month, day, year);
    }

    static QVariantList getDayList(int month, int year) {

        QVariantList dayList;

        int prevMonth = (((month - 1) + 11) % 12) + 1;

        int prevDays = prevMonth == 12 ? daysInMonth(prevMonth, year -1): daysInMonth(prevMonth, year);

        // Calculate the starting day of the month
        int startDay = dayOfWeek(1, month, year);

        // Print spaces for the days before the first day of the month
        for (int i = 1; i < startDay; ++i) {
            dayList << prevDays - (startDay - 2) + i;
        }

        // Print the days of the month
        for (int day = 1; day <= daysInMonth(month, year); ++day) {
            dayList << day;
        }

        return dayList;
    }

    static QVariantList getDayList(Date date) {

        int gridSize = 6 * 7;

        QVariantList dayList;

        int prevMonth = (((date.getMonth() - 1) + 11) % 12) + 1;

        int prevDays = prevMonth == 12 ? daysInMonth(prevMonth, date.getYear() -1): daysInMonth(prevMonth, date.getYear());

        // Calculate the starting day of the month
        int startDay = dayOfWeek(1, date.getMonth(), date.getYear());

        startDay += 7 * (startDay == 1);

        //std::cout << startDay << std::endl;

        // Print spaces for the days before the first day of the month
        for (int i = 1; i < startDay - 1; i++) {
            dayList << QDate(date.getYear() - (prevMonth == 12), prevMonth, prevDays - (startDay - 2) + i);
           // std::cout << date.getYear() - (prevMonth == 12) << " " << prevMonth << " " << prevDays - (startDay - 2) + i << std::endl;
        }

        // Print the days of the month
        for (int day = 1; day <= daysInMonth(date.getMonth(), date.getYear()); ++day) {
            dayList << QDate(date.getYear(), date.getMonth(), day);
        }
        for(int day = 1; dayList.size() < gridSize; day++) {
            int nextMonth = ((date.getMonth()) % 12) + 1;
            dayList << QDate(date.getYear() + (nextMonth == 1), nextMonth, day);
        }

        return dayList;
    }
};

// int main() {
//     int day, month, year;

//     // Get the current date
//     Calendar::getCurrentDate(day, month, year);
//     std::cout << "Current Date: " << day << "/" << month << "/" << year << std::endl;
//     std::cout << "Day: " << Calendar::dayOfWeek(day, month, year) << std::endl;

//     // Test the number of days in a month
//     int testMonth = 10;
//     int testYear = 2023;
//     std::cout << "Days in " << testMonth << "/" << testYear << ": " << Calendar::daysInMonth(testMonth, testYear) << std::endl;

//     // Test if a year is a leap year
//     std::cout << "Is " << testYear << " a leap year? " << (Calendar::isLeapYear(testYear) ? "Yes" : "No") << std::endl;

//     // Print the calendar for a given month and year
//     Calendar::printCalendar(testMonth, testYear);

//     Calendar::printCalendar(month, year);

//     return 0;
// }


// int main() {
//     int day, month, year;

//     // Get the current date
//     Calendar::getCurrentDate(day, month, year);
//     std::cout << "Current Date: " << day << "/" << month << "/" << year << std::endl;
//     std::cout << "Day: " << Calendar::dayOfWeek(day, month, year) << std::endl;

//     // Test the number of days in a month
//     int testMonth = 10;
//     int testYear = 2023;
//     std::cout << "Days in " << testMonth << "/" << testYear << ": " << Calendar::daysInMonth(testMonth, testYear) << std::endl;

//     // Test if a year is a leap year
//     std::cout << "Is " << testYear << " a leap year? " << (Calendar::isLeapYear(testYear) ? "Yes" : "No") << std::endl;

//     // Print the calendar for a given month and year
//     Calendar::printCalendar(testMonth, testYear);

//     Calendar::printCalendar(month, year);

//     return 0;
// }

// #include <iostream>
// #include "calendarone.h"


// // Function to check if a given year is a leap year
// bool Calendar::isLeapYear(int year) {
//     return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
// }

// // Function to calculate the number of days in a given month and year
// int Calendar::daysInMonth(int month, int year) {
//     if (month == 2) {
//         return Calendar::isLeapYear(year) ? 29 : 28; // February has 29 days in leap years
//     } else if (month == 4 || month == 6 || month == 9 || month == 11) {
//         return 30;
//     } else {
//         return 31;
//     }
// }

// // Function to print the calendar for a given month and year
// void Calendar::printCalendar(int month, int year) {
//     std::cout << "   ----- " << month << "/" << year << " -----\n";
//     std::cout << "Sun Mon Tue Wed Thu Fri Sat\n";

//     // Calculate the starting day of the month
//     int startDay = Calendar::dayOfWeek(1, month, year);

//     // Print spaces for the days before the first day of the month
//     for (int i = 1; i < startDay; ++i) {
//         std::cout << "    ";
//     }

//     // Print the days of the month
//     for (int day = 1; day <= Calendar::daysInMonth(month, year); ++day) {
//         printf("%3d ", day);
//         // Move to the next line after Saturday
//         if (++startDay > 7) {
//             startDay = 1;
//             std::cout << std::endl;
//         }
//     }
//     std::cout << std::endl;
// }

// // Function to calculate the day of the week for a given date
// int Calendar::dayOfWeek(int day, int month, int year) {
//     if (month < 3) {
//         month += 12;
//         year--;
//     }
//     int h = (day + 13 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
//     return h;
// }

// // Function to get the current date
// int Calendar::getCurrentDate(int &day, int &month, int &year) {
//     time_t now = time(0);
//     tm *ltm = localtime(&now);
//     day = ltm->tm_mday;
//     month = 1 + ltm->tm_mon;
//     year = 1900 + ltm->tm_year;
// }

// Date Calendar::getCurrentDate() {

//     time_t now = time(0);
//     tm *ltm = localtime(&now);
//     int day = ltm->tm_mday;
//     int month = 1 + ltm->tm_mon;
//     int year = 1900 + ltm->tm_year;

//     return Date(month, day, year);
// }

// QVariantList Calendar::getDayList(int month, int year) {

//     QVariantList dayList;

//     int prevMonth = (((month - 1) + 11) % 12) + 1;

//     int prevDays = prevMonth == 12 ? daysInMonth(prevMonth, year -1): daysInMonth(prevMonth, year);

//     // Calculate the starting day of the month
//     int startDay = dayOfWeek(1, month, year);

//     // Print spaces for the days before the first day of the month
//     for (int i = 1; i < startDay; ++i) {
//         dayList << prevDays - (startDay - 2) + i;
//     }

//     // Print the days of the month
//     for (int day = 1; day <= daysInMonth(month, year); ++day) {
//         dayList << day;
//     }

//     return dayList;
// }
