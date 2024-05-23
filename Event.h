//
// Created by Waosb on 03/02/2024.
//

#ifndef INC_376EVENTS_EVENT_H
#define INC_376EVENTS_EVENT_H

#include <string>
#include "Time_utils.h"
#include <QObject>
#include <QString>
#include <QDate>
#include <QTime>

using namespace std;

class Event : public QObject {
private:
    string title;
    string description;
    Time_utils start;
    Time_utils end;
    string location;

public:
    Event();

    Event(string name);

    Event(string name, string details);

    Event(string name, string details, Time_utils starting, Time_utils ending);

    Event(string name, Time_utils starting, Time_utils ending);

    Event(string name, string details, Time_utils starting, int length);

    Event(string name, Time_utils starting, int length);

    Event(string name, string details, int startH, int startMin, int endH, int endMin);

    Event(string name, int startH, int startMin, int endH, int endMin);

    Event(string name, string details, int startH, int startMin, int length);

    Event(string name, int startH, int startMin, int length);

    string getTitle();

    string getDescription();

    Time_utils getStart();

    Time_utils getEnd();

    string getLocation();

    void setTitle(string str);

    void setDescription(string str);

    void setStart(Time_utils t);

    void setStart(int h, int min);

    void setLocation(string str);

    int setEnd(Time_utils t);

    int setEnd(int h, int min);

    void setDuration(int num);

    string stringEvent() const;
};


#endif //INC_376EVENTS_EVENT_H
