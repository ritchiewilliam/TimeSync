#include <string>
#include <vector>
#include "Event.h"
#include "Time_utils.h"
#include "Task.h" // Include the header file for the Task class

// Constructor
Task::Task(std::string title, std::string description, Time_utils dueTime)
    : title(title), description(description), completed(false), dueTime(dueTime) {
}

// Getters
std::string Task::getTitle() const {
    return title;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

Time_utils Task::getDueTime() const {
    return dueTime;
}

const std::vector<Event*>& Task::getEventAssociations() const {
    return eventAssociations;
}

// Setters
void Task::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Task::setDescription(const std::string& newDescription) {
    description = newDescription;
}

void Task::setCompleted(bool isCompleted) {
    completed = isCompleted;
}

void Task::setDueTime(const Time_utils& newDueTime) {
    dueTime = newDueTime;
}

// Associate a new event with this task
void Task::associateEvent(Event* event) {
    eventAssociations.push_back(event);
}

// Disassociate an event from this task
bool Task::disassociateEvent(Event* event) {
    for (auto i = eventAssociations.begin(); i != eventAssociations.end(); ++i) {
        if (*i == event) {
            eventAssociations.erase(i);
            return true;
        }
    }
    return false; // Event not found
}

std::string Task::toString() const {
    std::string output = "Task Title: " + title + "\n"
                         "Description: " + description + "\n"
                         "Completed: " + (completed ? "Yes" : "No") + "\n"
                         "Due Time: " + dueTime.stringTime() + "\n";
    
    if (!eventAssociations.empty()) {
        output += "Associated Events:\n";
        for (const Event* event : eventAssociations) {
            output += event->stringEvent() + "\n"; 
        }
    } else {
        output += "No associated events.\n";
    }
    
    return output;
}
