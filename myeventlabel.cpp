#include "myeventlabel.h"
MyEventLabel::MyEventLabel(QWidget* parent, Event* _event) : EventLabel(parent)
{
    currEvent = _event;
    this->setStyleSheet("background-color: rgba(34, 24, 245, 50);text-align: center; ");
    this->setStyleSheet(((MainWindow*)this->parent())->myColorDefault);
    QFont font = this->font();
    font.setPointSize(10);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
    this->show();
    QObject::connect(this, SIGNAL(modifySignal(QMouseEvent *)), this, SLOT(modify(QMouseEvent *)));
    QObject::connect(this, SIGNAL(showDetailSignal(Event*)), (MainWindow*)this->parent(), SLOT(showDetail(Event*)));
}

//点击一次
void MyEventLabel::mousePressEvent(QMouseEvent *event) {
    //左键，显示高亮
    if(event->button() == Qt::LeftButton)
    {
        ((MainWindow*)parent())->eventsLoseFocus();
        this->setStyleSheet(((MainWindow*)this->parent())->myColorFocus);
        emit showDetailSignal(currEvent);
        event->accept();
    }
    //右键，编辑或删除
    else if(event->button() == Qt::RightButton)
    {
        ((MainWindow*)parent())->eventsLoseFocus();
        this->setStyleSheet("EventLabel {background-color: rgba(34, 24, 245, 90); text-align: center; }");
        this->setStyleSheet(((MainWindow*)this->parent())->myColorDefault);
        event->accept();
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
void MyEventLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        event->accept();
        emit modifySignal(event);
    }
}


void MyEventLabel::modify(QMouseEvent *event)
{
    QPoint pos = mapToParent(event->pos());
    OpenNew editWindow((MainWindow*)parent());
    editWindow.setGeometry(pos.x()+50,pos.y()-30,400,240);
    editWindow.setInit(pos.x(), pos.y());
    editWindow.showCurr(currEvent);
}
