#include "EventManager.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QStandardPaths>
#include <QDate>
#include <iostream>
EventManager::EventManager(QObject *parent) : QObject(parent) {
    loadEventsFromFile();
    viewEvent = createDefaultEvent();
}

EventManager::~EventManager() {
    //saveEventsToFile();
    clearEvents();
    delete(viewEvent);

}

void EventManager::addEvent(Q_Event* event) {
    events.append(event);
    saveEventsToFile();
    //emit eventsChanged();
}

void EventManager::createEvent(const QString &title, const QString &description, const QString &location, const QString &startTimeStr, const QString &endTimeStr,  const QString &dateStr) {
    QTime startTime = QTime::fromString(startTimeStr, "HH:mm");
    QTime endTime = QTime::fromString(endTimeStr, "HH:mm");

    QDate date = QDate::fromString(dateStr,"yyyy-MM-dd");

    if (!startTime.isValid() || !endTime.isValid()) {
        qDebug() << "Invalid time for event creation";
        return;
    }

    Q_Event *event = new Q_Event(this);
    event->setTitle(title);
    event->setDescription(description);
    event->setLocation(location);
    event->setStartTime(startTime);
    event->setEndTime(endTime);
    event->setDate(date);

    addEvent(event);
}

// QList<QObject*> EventManager::getEvents() const {
//     QList<QObject*> list;
//     for (Q_Event* event : events) {
//         list.append(event);
//     }
//     return list;
// }

// QList<Q_Event *> EventManager::getEvents() const {
//     std::cout << "EVENTS" << std::endl;
//     for(auto event : events) {
//         std::cout << event->getTitle().toStdString() << std::endl;
//     }
//     return events;
// }

void EventManager::updateEventList(const QDate &date) {
    viewEvents.clear();
    for(Q_Event * event : events) {
        if(event->getDate() == date) {
            int i;
            for(i = 0; i < viewEvents.length() && viewEvents[i]->getStartTime() <= event->getStartTime(); i++);
            viewEvents.insert(i, event);
        }
    }
    emit viewEventsChanged();
}

bool EventManager::checkForEvent(const QDate &date) {
    QDate correctedDate = date.addDays(-1);
    for(Q_Event * event : events) {
        if(event->getDate() == correctedDate) {
            return true;
        }
    }
    return false;
}

QList<Q_Event *> EventManager::getViewEvents() const {
    return viewEvents;
}

Q_Event * EventManager::getViewEvent() const{
    return viewEvent;
}

void EventManager::setViewEvent(Q_Event * event) {
    viewEvent = event;
    emit viewEventChanged();
}

void EventManager::testFunction() {
    qDebug() << "Test function called";
    printEventsToConsole();
}

void EventManager::saveEventsToFile() const {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/events.dat";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Cannot open file for writing");
        return;
    }

    QDataStream out(&file);
    for (const Q_Event *event : events) {
        qDebug() <<event->getTitle()<< " saved to file";
        out << event->getTitle() << event->getDescription() << event->getLocation()
            << event->getStartTime() << event->getEndTime() << event->getDate();
    }
    qDebug() << "event saved to file";
    file.close();
}

void EventManager::loadEventsFromFile() {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/events.dat";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading");
        return;
    }

    QDataStream in(&file);
    while (!in.atEnd()) {
        QString title, description, location;
        QTime startTime, endTime;
        QDate date;

        in >> title >> description >> location >> startTime >> endTime >> date;

        createEvent(title, description, location, startTime.toString("HH:mm"), endTime.toString("HH:mm"), date.toString("yyyy-MM-dd"));
    }

    file.close();
}

void EventManager::clearEvents() {
    qDeleteAll(events);
    events.clear();
}

Q_Event * EventManager::createDefaultEvent() {
    Q_Event * event = new Q_Event(this->parent());
    event->setTitle("");
    event->setDescription("");
    event->setLocation("");
    event->setStartTime(QTime(0, 0));
    event->setEndTime(QTime(0, 0));
    event->setDate(QDate(1970,1,1));

    return event;
}

void EventManager::printEventsToConsole() {
    qDebug() << "Printing existing events:";
    for (const auto *event : events) {
        if (event) {
            qDebug() << "Title:" << event->getTitle()
                     << ", Description:" << event->getDescription()
                     << ", Location:" << event->getLocation()
                     << ", Start Time:" << event->getStartTime().toString("HH:mm")
                     << ", End Time:" << event->getEndTime().toString("HH:mm")
                     << ", Date:" << event->getDate().toString("yyyy-MM-dd");
        }
    }
}

bool EventManager::removeEvent(const QString &title) {
    auto it = std::find_if(events.begin(), events.end(), [&title](const Q_Event *event) {
        return event->getTitle() == title;
    });


    if (it != events.end()) {
        Q_Event *eventToRemove = *it;
        qDebug() << "deleting " << eventToRemove->getTitle();
        events.erase(it);
        delete eventToRemove; // Free the memory used by the event
        saveEventsToFile(); // Update the file after removing the event
        //emit eventsChanged();
        return true;
    }

    return false;
}
