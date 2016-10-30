#include "createnew.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

CreateNew::CreateNew(QWidget* parent):QDialog(parent)
{
    setWindowTitle("create new event");
}

void CreateNew::setinit()
{
    QLabel *day_c = new QLabel(this);
    day_c->setGeometry(QRect(100, 200, 100, 30));
    day_c->setText("Day: ");

    day = new QLineEdit(this);
    day->setGeometry(200,200,100,30);

    QLabel *time_c = new QLabel(this);
    time_c->setGeometry(QRect(100,250,100,30));
    time_c->setText("Time: ");

    time1 = new QLineEdit(this);
    time1->setGeometry(200,250,100,30);

    QLabel *time_m = new QLabel(this);
    time_m->setGeometry(300,250,10,30);
    time_m->setText(" - ");

    time2 = new QLineEdit(this);
    time2->setGeometry(310,250,100,30);

    QPushButton *ok = new QPushButton ( "&OK", this);
    ok->setGeometry(400,400,80,40);
    ok->setStyleSheet("QPushButton {color: black;}");
    QObject::connect(ok, SIGNAL(clicked(bool)), SLOT(send()));


}
