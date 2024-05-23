#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QDate>

class menu : public QObject
{
    Q_OBJECT
public:
    explicit menu(QObject *parent = nullptr);

signals:

public slots:

    void callMe(const QDate &date);

};

// private:


#endif // MENU_H
