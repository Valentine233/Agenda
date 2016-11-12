#ifndef EVENTLABEL_H
#define EVENTLABEL_H

#include "opennew.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QFocusEvent>
#include <mainwindow.h>
class EventLabel : public QLabel
{
    Q_OBJECT

public:
    EventLabel(QWidget* parent=Q_NULLPTR, Event* event = Q_NULLPTR);
    Event* currEvent;

public slots:
    void modify(QMouseEvent *event);

signals:
    void modifySignal(QMouseEvent *event);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // EVENTLABEL_H
