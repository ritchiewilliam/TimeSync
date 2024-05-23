#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QString>
#include <QTime>
#include <QDateTime>
#include <QDate>

class Q_Event : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QTime startTime READ getStartTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QTime endTime READ getEndTime WRITE setEndTime NOTIFY endTimeChanged)
    Q_PROPERTY(QString location READ getLocation WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(QDate date READ getDate WRITE setDate NOTIFY dateChanged)

public:
    explicit Q_Event(QObject *parent = nullptr);

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getStartTimeStr() const;
    QTime getStartTime() const;
    void setStartTime(const QTime &value);

    QString getEndTimeStr() const;
    QTime getEndTime() const;
    void setEndTime(const QTime &value);

    Q_INVOKABLE QString getDateDisplay();
    Q_INVOKABLE QString getTimeDisplay();

    QString getLocation() const;
    void setLocation(const QString &value);

    QDate getDate() const;
    void setDate(const QDate &value);

signals:
    void titleChanged();
    void descriptionChanged();
    void startTimeChanged();
    void endTimeChanged();
    void locationChanged();
    void dateChanged();

private:
    QString title;
    QString description;
    QTime startTime;
    QTime endTime;
    QString location;
    QDate date;
};

#endif // EVENT_H
