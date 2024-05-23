// EventManager.h
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>
#include <QList>
#include "Q_Event.h"
#include <QDebug> 

class EventManager : public QObject {
    Q_OBJECT
public:
    explicit EventManager(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void addEvent(Q_Event* event) {
        events.append(event);
        emit eventsChanged();
    }

    Q_INVOKABLE void createEvent(const QString &title, const QString &description, const QString &location, const QString &startTimeStr, const QString &endTimeStr) {
        qDebug() << "creating event";
        QTime startTime = QTime::fromString(startTimeStr, "HH:mm");
        QTime endTime = QTime::fromString(endTimeStr, "HH:mm");

        if (!startTime.isValid() || !endTime.isValid()) {
            // Handle invalid time
            return;
        }

        Q_Event *event = new Q_Event(this);
        event->setTitle(title);
        event->setDescription(description);
        event->setLocation(location);
        event->setStartTime(startTime);
        event->setEndTime(endTime);
        events.append(event);
        emit eventsChanged();

        qDebug() << "Event submitted:" << title << description << location << startTimeStr << endTimeStr;
        printEvents(); 
    }

    void printEvents() {
        qDebug() << "Current list of events:";
        for (auto *event : events) {
            qDebug() << "Title:" << event->getTitle()
                    << ", Description:" << event->getDescription()
                    << ", Location:" << event->getLocation()
                    << ", Start Time:" << event->getStartTime().toString("HH:mm")
                    << ", End Time:" << event->getEndTime().toString("HH:mm");
        }
    }

    Q_INVOKABLE QList<Q_Event*> getEvents() const {
        QList<Q_Event*> list;
        for (Q_Event* event : events) {
            list.append(event);
        }
        return list;
    }

    Q_INVOKABLE void testFunction() {
        qDebug() << "Test function called successfully.";
    }

signals:
    void eventsChanged();

private:
    QList<Q_Event*> events;
};

#endif // EVENTMANAGER_H
