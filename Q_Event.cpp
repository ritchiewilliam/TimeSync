#include "Q_Event.h"

Q_Event::Q_Event(QObject *parent)
    : QObject(parent), date(QDate::currentDate()) {}

QString Q_Event::getTitle() const {
    //std::cout << title.toStdString() << std::endl;
    return title;
}

void Q_Event::setTitle(const QString &value) {
    if (title != value) {
        title = value;
        emit titleChanged();
    }
}

QString Q_Event::getDescription() const {
    return description;
}

void Q_Event::setDescription(const QString &value) {
    if (description != value) {
        description = value;
        emit descriptionChanged();
    }
}

QTime Q_Event::getStartTime() const {
    //std::cout << startTime.toString().toStdString() << std::endl;
    return startTime;
}

void Q_Event::setStartTime(const QTime &value) {
    if (startTime != value) {
        startTime = value;
        emit startTimeChanged();
    }
}

QTime Q_Event::getEndTime() const {
    //std::cout << endTime.toString().toStdString() << std::endl;
    return endTime;
}

void Q_Event::setEndTime(const QTime &value) {
    if (endTime != value) {
        endTime = value;
        emit endTimeChanged();
    }
}

QString Q_Event::getDateDisplay() {
    QString days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    return days[date.dayOfWeek() - 1] + ", " + date.toString("MMMM dd, yyyy");
}

QString Q_Event::getTimeDisplay() {
    return QString::number(startTime.hour()) + ':' + (startTime.minute() < 10 ? "0" : "") + QString::number(startTime.minute()) +
               " - " + QString::number(endTime.hour()) + ':' + (endTime.minute() < 10 ? "0" : "") + QString::number(endTime.minute());
}

void Q_Event::setLocation(const QString &value) {
    if (location != value) {
        location = value;
        emit locationChanged();
    }
}

QString Q_Event::getLocation() const {
    return location;
}

QDate Q_Event::getDate() const {
    return date;
}

void Q_Event::setDate(const QDate &value) {
    if (date != value) {
        date = value;
        emit dateChanged();
    }
}
