#include "monthcalendar.h"
#include "calendarone.cpp"

#include <QDateTime>

MonthCalendar::MonthCalendar(QObject *parent)
    : QObject{parent}
{
    viewDate = Calendar::getCurrentDate();
    today = Calendar::getCurrentDate();
    dayList = Calendar::getDayList(viewDate);
}


void MonthCalendar::selectDate(int day) {
    viewDate.setDay(day);
}

void MonthCalendar::switchMonth(bool nextMonth) {

    dayList.clear();

    if(nextMonth) {
        //Move to next month
        viewDate.setMonth(((viewDate.getMonth()) % 12) + 1);

        //Move to next year if January
        viewDate.setYear(viewDate.getYear() + (viewDate.getMonth() == 1));

        //Assign new day list for calendar
        setDayList(viewDate);
    }
    else {
        //Move to previous month
        viewDate.setMonth(((viewDate.getMonth() + 10) % 12) + 1);

        //Move to previous year if December
        viewDate.setYear(viewDate.getYear() - (viewDate.getMonth() == 12));

        //Assign new day list for calendar
        setDayList(viewDate);
    }

}

QVariantList MonthCalendar::getDayList() const {
    return dayList;
}

void MonthCalendar::setDayList(Date dateList) {
    dayList.clear();
    dayList = Calendar::getDayList(dateList);

    emit dayListChanged();
}

QDate MonthCalendar::getJSViewDate() {
    return viewDate.convertDate().addDays(1);
}

QDate MonthCalendar::getViewDate() {
    return viewDate.convertDate();
}

void MonthCalendar::setViewDate(QDate newDate) {

    // std::cout << newDate.toString().toStdString() << " old: " << viewDate.toString() << std::endl;

    std::cout << newDate.month() << " day: " << newDate.day() << std::endl;

    if(newDate.month() != viewDate.getMonth()) {
        //If the month is great or the year is greater it is the next year
        //And takes care of case where it is previous year
        switchMonth((newDate.month() > viewDate.getMonth() || newDate.year() > viewDate.getYear()) && newDate.year() >= viewDate.getYear());
    }

    viewDate.setDay(newDate.day());
    viewDate.setYear(newDate.year());

    emit viewDateChanged();
}

QDate MonthCalendar::getToday () {
    return today.convertDate().addDays(1);
}

