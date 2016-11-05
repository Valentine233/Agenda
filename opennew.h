#ifndef OPENNEW_H
#define OPENNEW_H

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

class OpenNew : public QDialog
{
    Q_OBJECT

public:
    OpenNew(QWidget* parent=nullptr);
    void setinit();

public slots:
    void TimeChoose(int id);

private:
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate(),this);
    QDateTimeEdit *starttime = new QDateTimeEdit(QTime::currentTime(),this);
    QDateTimeEdit *endtime = new QDateTimeEdit(QTime::currentTime(),this);

    QDateTimeEdit *startdate = new QDateTimeEdit(QDate::currentDate(),this);
    QDateTimeEdit *enddate = new QDateTimeEdit(QDate::currentDate(),this);
    QLabel* start1 = new QLabel(this);
    QLabel* end1 = new QLabel(this);
};

#endif // OPENNEW_H
