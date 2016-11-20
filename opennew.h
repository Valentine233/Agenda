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
#include <QMessageBox>

class OpenNew : public QDialog
{
    Q_OBJECT

public:
    OpenNew(QWidget* parent=Q_NULLPTR);
    void setInit(int, int);
    void showCurr(Event *);
    QPushButton* addButton = new QPushButton(this);
    QPushButton* confirmButton = new QPushButton(this);
    QPushButton* deleteButton = new QPushButton(this);
    QButtonGroup *weekdays = new QButtonGroup(this);
    QLabel *namevide = new QLabel(this);
    QLabel *diffDays = new QLabel(this);

signals:
    void transAdd(QString, QString, QDateTime, QDateTime, int);
    void transAddPl(QString,QString,QDate,QDate,QTime,QTime,int*,int);
    void transEdit(QString, QString, QDateTime, QDateTime, int, QString, QString, QDateTime, QDateTime);
    void transDelete(QString, QString, QDateTime, QDateTime, int);
    void deleteConfirm(QString, QString, QDateTime, QDateTime, int);

public slots:
    void TimeChoose(int id);
    void sendAdd();
    void sendEdit();
    void sendDelete();
    void deleteTemp();
    void deleteEventConfirm(QString name, QString place, QDateTime startTime, QDateTime endTime, int type);

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

    QString nameOld;
    QString placeOld;

    QDate dateOld;
    QTime starttimeOld;
    QTime endtimeOld;

    QDateTime startdateOld;
    QDateTime enddateOld;

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // OPENNEW_H
