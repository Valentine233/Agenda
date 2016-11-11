#include "eventlabel.h"

EventLabel::EventLabel(QWidget* parent) : QLabel(parent)
{
    QObject::connect(this, SIGNAL(modifySignal(QMouseEvent*)), this, SLOT(modify(QMouseEvent*)));

}
void EventLabel::mousePressEvent(QMouseEvent *event) {
    ((MainWindow*)parent())->eventsLoseFocus();
    this->setStyleSheet("EventLabel {background-color: rgba(34, 24, 245, 90); text-align: center; }");
    event->accept();
}

void EventLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if( event->buttons() == Qt::LeftButton)
    {
        emit modifySignal(event);
        event->accept();
    }
}
void EventLabel::modify(QMouseEvent *event)
{
//    OpenNew opennew((QWidget*)this->parent());
//    opennew.setGeometry(event->globalX()+50,event->globalY()-30,400,240);
//    opennew.setInit(event->x(), event->y());
//    opennew.exec();
}
