#include "event.h"
int Event::defaultDuration;
Event::Event(QString name, QString place, QDateTime starttime, QDateTime endtime, int type, QWidget *parent):
    QWidget(parent)
{
    eventName = name;
    eventPlace = place;
    eventStart = starttime;
    eventEnd = endtime;
    //eventStart = starttime.toString("yyyy.MM.dd HH:mm:ss");
    //eventEnd = endtime.toString("yyyy.MM.dd HH:mm:ss");
    eventType = type;
    //addtoCalendar(eventName,eventPlace,eventStart,eventEnd,eventType);
}


