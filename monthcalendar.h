#ifndef MONTHCALENDAR_H
#define MONTHCALENDAR_H

#include <QObject>
#include <QDate>
#include "Date.h"

class MonthCalendar : public QObject
{   
    Q_OBJECT

    //Properties to expose to QML
    Q_PROPERTY(QVariantList dayList READ getDayList() NOTIFY dayListChanged() FINAL)

    Q_PROPERTY(QDate viewDate READ getViewDate() WRITE setViewDate() NOTIFY viewDateChanged FINAL)

    Q_PROPERTY(QDate today READ getToday() NOTIFY todayChanged FINAL)

private:
    //The date that is currently being viewed by the calendar
    Date viewDate;

    //The current date
    Date today;

    //List of days displayed on the calendar
    QVariantList dayList;

public:
    explicit MonthCalendar(QObject *parent = nullptr);

    Q_INVOKABLE void refreshCalendar() { emit dayListChanged();}

    Q_INVOKABLE QDate getJSViewDate();

    QVariantList getDayList() const;

    void setDayList(Date listDate);

    QDate getViewDate();

    void setViewDate(QDate newDate);

    QDate getToday();

    void switchMonth(bool direction);

    void selectDate(int day);

signals:
    void dayListChanged();
    void viewDateChanged();
    void todayChanged();

};




#endif // MONTHCALENDAR_H
