#ifndef OPENNEW_H
#define OPENNEW_H

#include "db.h"
#include "event.h"
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QDebug>
#include <QDateTimeEdit>
#include <QDate>
#include <QPushButton>
#include <QCheckBox>
#include <QList>

class OpenNew : public QDialog
{
    Q_OBJECT

public:
    OpenNew(QWidget *parent);
    void setinit();

signals:
    void trans(QString, QString, QDateTime, QDateTime, int);

public slots:
    void TimeChoose(int id);
    //void addNewEvent(QString, QString, QDateTime, QDateTime, int);
    void send() //myevent: type = 0,   yourevent: type = 1
    {
        QDateTime start(dateEdit->date(), starttime->dateTime().time());
        QDateTime end(dateEdit->date(), endtime->dateTime().time());

        emit trans(nameinput->text(), placeinput->text(), start, end, 0);
    }

private:
    QLineEdit* nameinput = new QLineEdit(this);
    QLineEdit* placeinput = new QLineEdit(this);

    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate(),this);
    QDateTimeEdit *starttime = new QDateTimeEdit(QTime::currentTime(),this);
    QDateTimeEdit *endtime = new QDateTimeEdit(QTime::currentTime(),this);

    QDateTimeEdit *startdate = new QDateTimeEdit(QDate::currentDate(),this);
    QDateTimeEdit *enddate = new QDateTimeEdit(QDate::currentDate(),this);
    QLabel* start1 = new QLabel(this);
    QLabel* end1 = new QLabel(this);
};

#endif // OPENNEW_H
