#ifndef EVENTLABEL_H
#define EVENTLABEL_H

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
    EventLabel(QWidget* parent=Q_NULLPTR);
public slots:
    void modify(QMouseEvent*);
signals:
    void modifySignal(QMouseEvent *);
protected:
    void mousePressEvent(QMouseEvent *event);
//    void focusInEvent(QFocusEvent* e);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // EVENTLABEL_H
