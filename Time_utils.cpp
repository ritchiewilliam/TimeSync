//
// Created by Waosb on 03/02/2024.
//

#include "Time_utils.h"

Time_utils::Time_utils() {
    hour = 0;
    minute = 0;
}

Time_utils::Time_utils(int h) {
    if (checkHour(h)) {
        hour = h;
        minute = 0;
    }
}

Time_utils::Time_utils(int h, int min) {
    if (checkTime(h, min)) {
        hour = h;
        minute = min;
    }
}

int Time_utils::setTime(int h) {
    if (checkHour(h)) {
        hour = h;
        minute = 0;
        return 1;
    }
    return 0;
}

int Time_utils::setTime(int h, int min) {
    if (checkTime(h, min)) {
        hour = h;
        minute = min;
        return 1;
    }
    return 0;
}

int Time_utils::setHour(int h) {
    if (checkHour(h)) {
        hour = h;
        return 1;
    }
    return 0;
}

int Time_utils::setMin(int min) {
    if (checkMin(min)) {
        minute = min;
        return 1;
    }
    return 0;
}

int Time_utils::getHour() {
    return hour;
}

int Time_utils::getMin() {
    return minute;
}

string Time_utils::stringTime() const{
    char temp[6];
    ::sprintf(temp, "%02d:%02d", hour, minute);
    return temp;
}

bool Time_utils::checkHour(int h) {
    return h >= 0 && h <= 24;
}

bool Time_utils::checkMin(int min) {
    return min >= 0 && min <= 60;
}

bool Time_utils::checkTime(int h, int min) {
    return checkHour(h) && checkMin(min);
}
