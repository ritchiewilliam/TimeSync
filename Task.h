#include <string>
#include <vector>
#include "Event.h"
#include "Time_utils.h"

class Task {
private:
    std::string title;
    std::string description;
    bool completed;
    std::vector<Event*> eventAssociations; // Pointers to associated events
    Time_utils dueTime;

public:
    // Constructors
    Task(std::string title, std::string description, Time_utils dueTime);
    // Getters
    std::string getTitle() const;
    std::string getDescription() const;
    bool isCompleted() const;
    Time_utils getDueTime() const;
    const std::vector<Event*>& getEventAssociations() const;
    // Setters
    void setTitle(const std::string& newTitle);
    void setDescription(const std::string& newDescription);
    void setCompleted(bool isCompleted);
    void setDueTime(const Time_utils& newDueTime);
    void associateEvent(Event* event);
    bool disassociateEvent(Event* event);
    std::string toString() const;

};
