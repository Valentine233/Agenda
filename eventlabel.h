#ifndef EVENTLABEL_H
#define EVENTLABEL_H

#include "mainwindow.h"
#include "opennew.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QMenu>
#include <QAction>
#include <QPoint>

class EventLabel : public QLabel
{
    Q_OBJECT

public:
    EventLabel(QWidget* parent=Q_NULLPTR, Event* event = Q_NULLPTR);
    Event* currEvent;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // EVENTLABEL_H
