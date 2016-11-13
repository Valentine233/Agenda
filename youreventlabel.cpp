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

