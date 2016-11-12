#include "eventlabel.h"

EventLabel::EventLabel(QWidget* parent) : QLabel(parent)
{
    QObject::connect(this, SIGNAL(modifySignal(QMouseEvent *)), this, SLOT(modify(QMouseEvent *)));

}

//点击一次，显示高亮
void EventLabel::mousePressEvent(QMouseEvent *event) {
    ((MainWindow*)parent())->eventsLoseFocus();
    this->setStyleSheet("EventLabel {background-color: rgba(34, 24, 245, 90); text-align: center; }");
    event->accept();  //what to do with accept?
}

//点击两次，修改或删除事件
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
    qDebug() << "enter modify\n";
    Event* curr_event =  ((MainWindow*)parent())->findEvent(event);
    qDebug() << curr_event->eventName << curr_event->eventPlace  << curr_event->eventStart.date() << curr_event->eventStart.time()<<"\n";
    OpenNew editWindow((MainWindow*)parent());
    editWindow.setGeometry(event->globalX()+50,event->globalY()-30,400,240);
    editWindow.setInit(event->x(), event->y());
    editWindow.showCurr(curr_event);
}
