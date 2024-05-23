//
// Created by Waosb on 03/02/2024.
//

#ifndef INC_376EVENTS_TIME_H
#define INC_376EVENTS_TIME_H

#include <string>

using namespace std;

class Time_utils {
private:
    int hour;
    int minute;
    bool checkHour(int h);
    bool checkMin(int min);
    bool checkTime(int h, int min);

public:
    Time_utils();
    Time_utils(int h, int min);
    Time_utils(int h);

    int setTime(int h, int min);
    int setTime(int h);

    int setHour(int h);
    int setMin(int min);

    int getHour();
    int getMin();
    string stringTime() const;
};


#endif //INC_376EVENTS_TIME_H
