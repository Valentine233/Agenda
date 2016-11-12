#include "eventlabel.h"

EventLabel::EventLabel(QWidget* parent, Event* _event) : QLabel(parent)
{
    currEvent = _event;
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
        event->accept();
        emit modifySignal(event);

    }
}


void EventLabel::modify(QMouseEvent *event)
{
    QPoint pos = mapToParent(event->pos());
    OpenNew editWindow((MainWindow*)parent());
    editWindow.setGeometry(pos.x()+50,pos.y()-30,400,240);
    editWindow.setInit(pos.x(), pos.y());
    editWindow.showCurr(currEvent);
}
