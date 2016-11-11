#ifndef EVENT_H
#define EVENT_H

#include <QString>
#include <QDateTime>
#include <QWidget>
#include <QLabel>

class Event : public QWidget
{
public:
    Event(QString name, QString place, QDateTime starttime, QDateTime endtime, int type,
          QWidget *parent);
    QString eventName;
    QString eventPlace;
    QDateTime eventStart;
    QDateTime eventEnd;
    //QString eventStart;
    //QString eventEnd;
    int eventType;
    QLabel *eventUI = NULL;

    // in minute
    static int defaultDuration;

//signals:
//    void removeMyUI();

};

#endif // EVENT_H
