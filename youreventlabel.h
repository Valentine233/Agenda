#ifndef YOUREVENTLABEL_H
#define YOUREVENTLABEL_H

#include "eventlabel.h"
#include "mainwindow.h"
#include "opennew.h"
#include <QMenu>
#include <QAction>
#include <QPoint>
class YourEventLabel : public EventLabel
{
    Q_OBJECT

public:
    YourEventLabel(QWidget* parent=Q_NULLPTR, Event* event = Q_NULLPTR);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // YOUREVENTLABEL_H
