#include "youreventlabel.h"

YourEventLabel::YourEventLabel(QWidget* parent, Event* _event) : EventLabel(parent)
{
    currEvent = _event;
    eventRect->setStyleSheet("background-color: rgba(235, 34, 145, 50);text-align: center; ");
    QFont font = eventRect->font();
    font.setPointSize(10);
    eventRect->setFont(font);
    eventRect->setAlignment(Qt::AlignCenter);
    eventRect->show();
}

//点击一次
void YourEventLabel::mousePressEvent(QMouseEvent *event) {
    // 无修改权限
}

//点击两次
void YourEventLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 无修改权限
}

