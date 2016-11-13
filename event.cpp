#include "event.h"

int Event::defaultDuration;

Event::Event(QString name, QString place, QDateTime starttime, QDateTime endtime, int type, QWidget *parent):
    QWidget(parent)
{
    eventName = name;
    eventPlace = place;
    eventStart = starttime;
    eventEnd = endtime;
    eventType = type;
}
