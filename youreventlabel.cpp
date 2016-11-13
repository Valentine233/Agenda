#include "youreventlabel.h"

YourEventLabel::YourEventLabel(QWidget* parent, Event* _event, QLabel* _label) : EventLabel(parent)
{
    currEvent = _event;
    rightLabel = _label;
    this->setStyleSheet("background-color: rgba(240, 54, 60, 50);text-align: center; ");
    QFont font = this->font();
    font.setPointSize(10);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
    this->show();
}

//点击一次
void YourEventLabel::mousePressEvent(QMouseEvent *event) {
    //左键，显示高亮
    if(event->button() == Qt::LeftButton)
    {
        ((MainWindow*)parent())->eventsLoseFocus();
        this->setStyleSheet("EventLabel {background-color: rgba(240, 54, 60, 90); text-align: center; }");
        rightLabel->setGeometry(800,0,200,600);
        rightLabel->setText("事件名称：  "+currEvent->eventName+"\n"+"事件地点：  "+currEvent->eventPlace+"\n"
                            +"事件日期： "+currEvent->eventStart.date().toString("yyyy/MM/dd")+"\n"
                            +"开始时间： "+currEvent->eventStart.time().toString("HH:mm")+"\n"
                            +"结束时间： "+currEvent->eventEnd.time().toString("HH:mm"));
        rightLabel->show();
        event->accept();
    }
    //右键，无修改权限
}

//点击两次
void YourEventLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 无修改权限
}

