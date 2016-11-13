#include "eventlabel.h"

EventLabel::EventLabel(QWidget* parent, Event* _event) : QLabel(parent)
{
    currEvent = _event;
}
