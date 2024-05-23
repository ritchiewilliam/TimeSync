#include "menu.h"
#include <QDebug>

menu::menu(QObject *parent)
    : QObject{parent}
{

}

void menu::callMe(const QDate &date) {

    qDebug() << date.toString();
}
