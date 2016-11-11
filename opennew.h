#ifndef OPENNEW_H
#define OPENNEW_H

#include "mainwindow.h"
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
    OpenNew(QWidget* parent=Q_NULLPTR);
    void setInit(int, int);

signals:
    void trans(QString, QString, QDateTime, QDateTime, int);

public slots:
    void TimeChoose(int id);
    void addNewEvent(QString, QString, QDateTime, QDateTime, int);
    void send();
    void deleteTemp();

private:
    QLineEdit* nameinput = new QLineEdit(this);
    QLineEdit* placeinput = new QLineEdit(this);

    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate(),this);
    QTimeEdit *starttime = new QTimeEdit(QTime::currentTime(),this);
    QTimeEdit *endtime = new QTimeEdit(QTime::currentTime(),this);

    QDateTimeEdit *startdate = new QDateTimeEdit(QDate::currentDate(),this);
    QDateTimeEdit *enddate = new QDateTimeEdit(QDate::currentDate(),this);
    QLabel* start1 = new QLabel(this);
    QLabel* end1 = new QLabel(this);
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // OPENNEW_H
