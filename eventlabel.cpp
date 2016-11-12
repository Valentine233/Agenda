#include "eventlabel.h"

EventLabel::EventLabel(QWidget* parent, Event* _event) : QLabel(parent)
{
    currEvent = _event;
    QObject::connect(this, SIGNAL(modifySignal(QMouseEvent *)), this, SLOT(modify(QMouseEvent *)));

}

//点击一次
void EventLabel::mousePressEvent(QMouseEvent *event) {
    //左键，显示高亮
    if(event->button() == Qt::LeftButton)
    {
        ((MainWindow*)parent())->eventsLoseFocus();
        this->setStyleSheet("EventLabel {background-color: rgba(34, 24, 245, 90); text-align: center; }");
        event->accept();
    }
    //右键，编辑或删除
    else if(event->button() == Qt::RightButton)
    {
//        ((MainWindow*)parent())->eventsLoseFocus();
//        this->setStyleSheet("EventLabel {background-color: rgba(34, 24, 245, 90); text-align: center; }");

//        QMenu *menu = new QMenu(this);
//        QAction *editAction = new QAction("编辑", this);
//        menu->addAction(editAction);
//        connect(editAction, SIGNAL(triggered()), this, SLOT(menuModify()));
//        QAction *deleteAction = new QAction("删除", this);
//        OpenNew editWindow((MainWindow*)parent());
//        connect(deleteAction, SIGNAL(deleteConfirmSign(QString, QString, QDateTime, QDateTime, int)), editWindow, SLOT(deleteEventConfirm(QString, QString, QDateTime, QDateTime, int)));
//        menu->addAction(deleteAction);
//        menu->show();
//        event->accept();
    }

}

//点击两次，修改或删除事件
void EventLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
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
