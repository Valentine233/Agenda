#ifndef MYEVENTLABEL_H
#define MYEVENTLABEL_H
#include "eventlabel.h"
#include "event.h"
#include "mainwindow.h"
#include "opennew.h"
#include <QMenu>
#include <QAction>
#include <QPoint>
class EventLabel;
class MyEventLabel : public EventLabel
{
    Q_OBJECT

public:
    MyEventLabel(QWidget* parent=Q_NULLPTR, Event* event = Q_NULLPTR);

public slots:
    void modify(QMouseEvent *event);

signals:
    void modifySignal(QMouseEvent *event);
    void deleteConfirmSign(QString name, QString place, QDateTime startTime, QDateTime endTime, int type);
    void showDetailSignal(Event*);


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // MYEVENTLABEL_H
