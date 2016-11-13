#include "eventlabel.h"

EventLabel::EventLabel(QWidget* parent, Event* _event, QLabel* _label) : QLabel(parent)
{
    currEvent = _event;
    rightLabel = _label;
}
