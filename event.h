#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

QFile MyEventList("/Users/liaoxuan/QtProjet/Agenda/MyEventList.txt");
QFile YourEventList("/Users/liaoxuan/QtProjet/Agenda/YourEventList.txt");
QTextStream MyEvent(&MyEventList);
QTextStream YourEvent(&YourEventList);

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
