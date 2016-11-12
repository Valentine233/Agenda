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

public slots:
    void modify(QMouseEvent *event);

signals:
    void modifySignal(QMouseEvent *event);
    void deleteConfirmSign(QString name, QString place, QDateTime startTime, QDateTime endTime, int type);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // EVENTLABEL_H
