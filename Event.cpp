//
// Created by Waosb on 03/02/2024.
//

#include "Event.h"
#include "Time_utils.h"

using namespace std;

Event::Event() {
    title = "";
    description = "";
    start = Time_utils();
    end = Time_utils();
}

Event::Event(string name) {
    title = name;
    description = "";
    start = Time_utils();
    end = Time_utils();
}

Event::Event(string name, string details) {
    title = name;
    description = details;
    start = Time_utils();
    end = Time_utils();
}

Event::Event(string name, string details, Time_utils starting, Time_utils ending) {
    title = name;
    description = details;
    start = starting;
    end = ending;
}

Event::Event(string name, Time_utils starting, Time_utils ending) {
    title = name;
    description = "";
    start = starting;
    end = ending;
}

Event::Event(string name, string details, Time_utils starting, int length) {
    title = name;
    description = details;
    start = starting;
    setDuration(length);
}

Event::Event(string name, Time_utils starting, int length) {
    title = name;
    description = "";
    start = starting;
    setDuration(length);
}

Event::Event(string name, string details, int startH, int startMin, int endH, int endMin) {
    title = name;
    description = details;
    start = Time_utils(startH, startMin);
    end = Time_utils(endH, endMin);
}

Event::Event(string name, int startH, int startMin, int endH, int endMin) {
    title = name;
    description = "";
    start = Time_utils(startH, startMin);
    end = Time_utils(endH, endMin);
}

Event::Event(string name, string details, int startH, int startMin, int length) {
    title = name;
    description = details;
    start = Time_utils(startH, startMin);
    setDuration(length);
}

Event::Event(string name, int startH, int startMin, int length) {
    title = name;
    description = "";
    start = Time_utils(startH, startMin);
    setDuration(length);
}

string Event::getTitle() {
    return title;
}

string Event::getDescription() {
    return description;
}

Time_utils Event::getStart() {
    return start;
}

Time_utils Event::getEnd() {
    return end;
}

string Event::getLocation() {
    return location;
}

void Event::setTitle(string str) {
    title = str;
}

void Event::setDescription(string str) {
    description = str;
}

void Event::setStart(Time_utils t) {
    start.setTime(t.getHour(), t.getMin());
}

void Event::setStart(int h, int min) {
    start.setTime(h, min);
}

void Event::setLocation(string str) {
    location = str;
}

int Event::setEnd(Time_utils t) {
    if (t.getHour() > start.getHour() || (t.getHour() == start.getHour() && t.getMin() > start.getMin())) {
        end.setTime(t.getHour(), t.getMin());
        return 1;
    }
    return 0;
}

int Event::setEnd(int h, int min) {
    if (h > start.getHour() || (h == start.getHour() && min > start.getMin())) {
        end.setTime(h, min);
        return 1;
    }
    return 0;
}

void Event::setDuration(int num) {
    end.setTime(start.getHour(), start.getMin());
    while (num + start.getMin() > 60) {
        end.setHour(end.getHour() + 1);
        num -= 60;
    }
    end.setMin(num + start.getMin());
}

string Event::stringEvent() const{
    return "Event Title: " + title + "\n"
    + "Description: " + description + "\n"
    + "Begins at " + start.stringTime() + "\n"
    + "Ends at " + end.stringTime() + "\n";
}
