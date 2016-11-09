#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>


class Event
{
public:
    Event(QString name, QString place, QDateTime starttime, QDateTime endtime);

private:
    QString eventName;
    QString eventPlace;
    QDateTime eventStarttime;
    QDateTime eventEndtime;
};

#endif // EVENT_H
