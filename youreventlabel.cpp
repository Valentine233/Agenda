#include "youreventlabel.h"

YourEventLabel::YourEventLabel(QWidget* parent, Event* _event) : EventLabel(parent)
{
    currEvent = _event;
    this->setStyleSheet("background-color: rgba(240, 54, 60, 50);text-align: center; ");
    QFont font = this->font();
    font.setPointSize(10);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
    this->show();
    QObject::connect(this, SIGNAL(showDetailSignal(Event*)), (MainWindow*)this->parent(), SLOT(showDetail(Event*)));
}

//点击一次
void YourEventLabel::mousePressEvent(QMouseEvent *event) {
    //左键，显示高亮
    if(event->button() == Qt::LeftButton)
    {
        ((MainWindow*)parent())->eventsLoseFocus();
        this->setStyleSheet(((MainWindow*)this->parent())->yourColorFocus);
        emit showDetailSignal(currEvent);
        event->accept();
    }
    // 无修改权限
}

//点击两次
void YourEventLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 无修改权限
}

