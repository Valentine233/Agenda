#ifndef EVENT_H
#define EVENT_H

#include "mainwindow.h"
#include <QString>
#include <QDateTime>
#include <QList>
#include <QWidget>

class Event : public QWidget
{
public:
    friend class MainWindow;
    Event(QString name, QString place, QDateTime starttime, QDateTime endtime, int type);
    //static QList<Event>* mylist;
    //static QList<Event>* yourlist;
    void paintEvent(QPaintEvent *);

private:
    QString eventName;
    QString eventPlace;
    QDateTime eventStart;
    QDateTime eventEnd;
    //QString eventStart;
    //QString eventEnd;
    int eventType;
};

#endif // EVENT_H
