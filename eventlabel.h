#ifndef EVENTLABEL_H
#define EVENTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QFocusEvent>
#include "event.h"
class Event;
class EventLabel : public QLabel
{
    Q_OBJECT

public:
    EventLabel(QWidget* parent=Q_NULLPTR, Event* event = Q_NULLPTR);
    Event* currEvent;

signals:
    void showDetailSignal(Event*);

protected:
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) = 0;
};

#endif // EVENTLABEL_H
