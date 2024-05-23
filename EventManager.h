#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>
#include <QList>
#include <QTime>
#include "Q_Event.h"

class EventManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<Q_Event*> viewEvents READ getViewEvents NOTIFY viewEventsChanged)
    Q_PROPERTY(Q_Event * viewEvent READ getViewEvent WRITE setViewEvent NOTIFY viewEventChanged)
public:
    explicit EventManager(QObject *parent = nullptr);
    ~EventManager();

    Q_INVOKABLE void addEvent(Q_Event* event);
    Q_INVOKABLE void createEvent(const QString &title, const QString &description, const QString &location, const QString &startTimeStr, const QString &endTimeStr, const QString &dateStr);

    Q_INVOKABLE void updateEventList(const QDate &date);
    //Q_INVOKABLE QList<QObject*> getEvents() const;

    Q_INVOKABLE bool checkForEvent(const QDate &date);

    Q_INVOKABLE void testFunction();

    QList<Q_Event *> getViewEvents() const;

    Q_Event * getViewEvent() const;

    void setViewEvent(Q_Event * event);

    void printEventsToConsole(); // Add this line
    Q_INVOKABLE bool removeEvent(const QString &title);

signals:
    //void eventsChanged();
    void viewEventsChanged();
    void viewEventChanged();

private:
    QList<Q_Event*> events;
    QList<Q_Event*> viewEvents;
    Q_Event * viewEvent = nullptr;

    Q_Event * createDefaultEvent();
    void saveEventsToFile() const;
    void loadEventsFromFile();
    void clearEvents();
};

#endif // EVENTMANAGER_H
