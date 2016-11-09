#include "event.h"

QTextStream MainWindow::MyEvent;

Event::Event(QString name, QString place, QDateTime starttime, QDateTime endtime)
{
    eventName = name;
    eventPlace = place;
    eventStarttime = starttime;
    eventEndtime = endtime;
    QString start = eventStarttime.toString("yyyy.MM.dd HH:mm:ss");
    QString end = eventEndtime.toString("yyyy.MM.dd HH:mm:ss");
}
