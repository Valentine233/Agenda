#include "opennew.h"

//QList<Event*>* MainWindow::list;
//QList<Event*>* MainWindow::yourlist;
void AddEvent(QString, QString, QString, QString);

OpenNew::OpenNew(QWidget* parent):QDialog(parent)
{
    setWindowTitle("New");
}

void OpenNew::setInit(int x, int y)
{
    QTime* eventStartTime;
    QDate eventDay;
    QString weekStrings[7] = {"周一","周二","周三","周四","周五","周六","周日"};

    if(x==-1 && y==-1)    //generalEvent
    {
        QTime* time = new QTime(MainWindow::curr_time.time());
        eventStartTime = time;
        eventDay = MainWindow::curr_time.date();
    }
    else    //specialEvent
    {
        // y 5 for 15 min, 20 for 1 hour， a grid is 40 - 2 hours
        QTime* time = new QTime((y- MainWindow::topY)/(MainWindow::gridHight/2), (y- MainWindow::topY)%(MainWindow::gridHight/2)/((MainWindow::gridHight/4))*30);
        eventStartTime = time;
        QString currDay = MainWindow::curr_time.toString("ddd");
        int d;
        for (d=0;d<7;d++) {
            if (weekStrings[d] == currDay)
                break;
        }
        eventDay = MainWindow::curr_time.date().addDays((x-MainWindow::leftX)/(MainWindow::gridWidth*2)-d);
    }

    QLabel* name = new QLabel(this);
    name->setText("事件名称：");
    name->setGeometry(QRect(20,10,60,20));

    nameinput->setGeometry(QRect(100,10,100,20));

    QLabel* place = new QLabel(this);
    place->setText("事件地点：");
    place->setGeometry(QRect(20,40,60,20));

    placeinput->setGeometry(QRect(100,40,100,20));

    QLabel* time = new QLabel(this);
    time->setText("时间类型：");
    time->setGeometry(QRect(20,70,60,20));

    QString timetype[] = {"单次事件","重复事件"};
    QButtonGroup* timechoise = new QButtonGroup(this);
    for(int i=0; i<2 ; i++)
    {
        QRadioButton* choise = new QRadioButton(this);
        choise->setText(timetype[i]);
        choise->setGeometry(100+100*i,70,100,20);
        timechoise->addButton(choise,i+1);
    }
    timechoise->button(1)->click();

    //单次日期
    dateEdit->setDate(eventDay);
    dateEdit->setDisplayFormat("yyyy/MM/dd");
    dateEdit->setGeometry(20,105,150,25);

    //重复日期

    start1->setText("从");
    start1->setGeometry(QRect(20,108,20,20));
    start1->hide();

    startdate->setDate(eventDay);
    startdate->setDisplayFormat("yyyy/MM/dd");
    startdate->setGeometry(40,105,150,25);
    startdate->hide();

    end1->setText("至");
    end1->setGeometry(QRect(200,108,20,20));
    end1->hide();

    enddate->setDate(eventDay);
    enddate->setDisplayFormat("yyyy/MM/dd");
    enddate->setGeometry(220,105,150,25);
    enddate->hide();

    //时间
    QLabel* start2 = new QLabel(this);
    start2->setText("从");
    start2->setGeometry(QRect(20,143,20,20));
    starttime->setTime(*eventStartTime);
    starttime->setDisplayFormat("HH:mm");
    starttime->setGeometry(40,140,150,25);

    QLabel* end2 = new QLabel(this);
    end2->setText("至");
    end2->setGeometry(QRect(200,143,20,20));

    endtime->setTime(eventStartTime->addSecs(60*Event::defaultDuration));
    endtime->setDisplayFormat("HH:mm");
    endtime->setGeometry(220,140,150,25);

    //week选项
    weekdays->setExclusive(false);
    for(int i=0; i<7; i++)
    {
        QCheckBox* weekday = new QCheckBox(weekStrings[i], this);
        weekday->setGeometry(20+50*i,180,50,20);
        weekday->hide();
        weekdays->addButton(weekday,i);
    }

    addButton->setText("添加");
    addButton->setGeometry(QRect(300,190,40,20));
    addButton->setStyleSheet("QPushButton {color: black;}");

    QObject::connect(timechoise, SIGNAL(buttonPressed(int)), this, SLOT(TimeChoose(int)));
    QObject::connect(addButton, SIGNAL(clicked(bool)), this, SLOT(sendAdd()));
    QObject::connect(this, SIGNAL(transAdd(QString, QString, QDateTime, QDateTime, int)), this->parent(),
                     SLOT(createNewEvent(QString,QString,QDateTime, QDateTime, int)));
    QObject::connect(this, SIGNAL(transAddPl(QString,QString,QDate,QDate,QTime,QTime,int*,int)), this->parent(),
                     SLOT(createNewEventPl(QString,QString,QDate,QDate,QTime,QTime,int*,int)));
    QObject::connect(this, SIGNAL(transAdd(QString, QString, QDateTime, QDateTime, int)), this, SLOT(close()));
    QObject::connect(this, SIGNAL(transAddPl(QString,QString,QDate,QDate,QTime,QTime,int*,int)), this, SLOT(close()));

    confirmButton->setText("确认");
    confirmButton->setGeometry(QRect(300,210,40,20));
    confirmButton->setStyleSheet("QPushButton {color: black;}");
    confirmButton->hide();

    QObject::connect(confirmButton, SIGNAL(clicked(bool)), this, SLOT(sendEdit()));
    QObject::connect(this, SIGNAL(transEdit(QString, QString, QDateTime, QDateTime, int, QString, QString, QDateTime, QDateTime)),
                     this->parent(), SLOT(editEvent(QString, QString, QDateTime, QDateTime, int, QString, QString, QDateTime, QDateTime)));
    QObject::connect(this, SIGNAL(transEdit(QString, QString, QDateTime, QDateTime, int, QString, QString, QDateTime, QDateTime)),
                     this, SLOT(close()));

    deleteButton->setText("删除");
    deleteButton->setGeometry(QRect(200,210,40,20));
    deleteButton->setStyleSheet("QPushButton {color: black;}");
    deleteButton->hide();

    QObject::connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(sendDelete()));
    QObject::connect(this, SIGNAL(transDelete(QString,QString,QDateTime,QDateTime,int)),
                     this, SLOT(deleteEventConfirm(QString, QString, QDateTime, QDateTime, int)));
    QObject::connect(this, SIGNAL(deleteConfirm(QString,QString,QDateTime,QDateTime,int)),
                     this->parent(), SLOT(deleteEvent(QString, QString, QDateTime, QDateTime, int)));
    QObject::connect(this, SIGNAL(deleteConfirm(QString,QString,QDateTime,QDateTime,int)),
                     this, SLOT(close()));

    // build a temp event
    Event *tempEvent = new Event("未命名","",QDateTime(dateEdit->date(), starttime->dateTime().time()),QDateTime(dateEdit->date(), endtime->dateTime().time()),0,this);
    ((MainWindow*)this->parent())->tempUI = ((MainWindow*)this->parent())->addEventUI(tempEvent);
}

void OpenNew::sendAdd() //myevent: type = 0,   yourevent: type = 1
{
    connect(this, SIGNAL(diffDaysSignal()), this, SLOT(diffDaysWarning()));
    QDateTime start(dateEdit->date(), starttime->dateTime().time());
    QDateTime end(dateEdit->date(), endtime->dateTime().time());
    QDate sdate(startdate->date());
    QDate edate(enddate->date());
    QTime stime(starttime->dateTime().time());
    QTime etime(endtime->dateTime().time());
    int id[7] = {0};
    for(int i=0; i<7; i++)
    {
        if(weekdays->button(i)->isChecked())
            id[i] = 1;
    }
    deleteTemp();
    if(start.time() > end.time())
    {
        emit diffDaysSignal();
    }
    else if(startdate->isHidden() && enddate->isHidden())
    {
        emit transAdd(nameinput->text(), placeinput->text(), start, end, 0);
    }
    else
    {
        emit transAddPl(nameinput->text(), placeinput->text(), sdate, edate, stime, etime, id, 0);
    }
}

void OpenNew::sendEdit()
{
    QDateTime start(dateEdit->date(), starttime->dateTime().time());
    QDateTime end(dateEdit->date(), endtime->dateTime().time());

    QDateTime startOld(dateOld, starttimeOld);
    QDateTime endOld(dateOld, endtimeOld);
    emit transEdit(nameinput->text(), placeinput->text(), start, end, 0, nameOld, placeOld, startOld, endOld);
}

void OpenNew::sendDelete()
{
    QDateTime start(dateEdit->date(), starttime->dateTime().time());
    QDateTime end(dateEdit->date(), endtime->dateTime().time());
    emit transDelete(nameinput->text(), placeinput->text(), start, end, 0);
}

void OpenNew::deleteTemp()
{
    if (((MainWindow*)this->parent())->tempUI != NULL) {
        delete ((MainWindow*)this->parent())->tempUI;
        ((MainWindow*)this->parent())->tempUI = NULL;
    }
}

void OpenNew::closeEvent(QCloseEvent *event) {
    deleteTemp();
}

void OpenNew::TimeChoose(int id)
{

    if(id==1) //单次事件
    {
        for(int i=0; i<weekdays->buttons().length(); i++)
        {
            weekdays->button(i)->hide();
        }
        addButton->setGeometry(QRect(300,190,40,20));
        startdate->hide();
        enddate->hide();
        start1->hide();
        end1->hide();
        dateEdit->show();
        starttime->show();
        endtime->show();
    }
    else if(id==2) //重复事件
    {
        dateEdit->hide();
        for(int i=0; i<weekdays->buttons().length(); i++)
        {
            weekdays->button(i)->show();
        }
        addButton->setGeometry(QRect(300,210,40,20));
        startdate->show();
        enddate->show();
        start1->show();
        end1->show();
    }

}

void OpenNew::showCurr(Event *event)
{
    setWindowTitle("Edit");
    nameinput->setText(event->eventName);
    nameOld = event->eventName;
    placeinput->setText(event->eventPlace);
    placeOld = event->eventPlace;
    dateEdit->setDate(event->eventStart.date());
    dateOld = event->eventStart.date();
    starttime->setTime(event->eventStart.time());
    starttimeOld = event->eventStart.time();
    endtime->setTime(event->eventEnd.time());
    endtimeOld = event->eventEnd.time();
    addButton->hide();
    confirmButton->show();
    deleteButton->show();
    ((MainWindow*)this->parent())->tempUI->hide();
    this->exec();
}

void OpenNew::deleteEventConfirm(QString name, QString place, QDateTime startTime, QDateTime endTime, int type)
{
    QMessageBox messageBox(this);
    messageBox.setText("确定删除事件么？");
    QAbstractButton *notDeleteBt = messageBox.addButton(QMessageBox::No);
    QAbstractButton *deleteBt = messageBox.addButton(QMessageBox::Yes);
    messageBox.exec();
    if (messageBox.clickedButton() == deleteBt) {
        emit deleteConfirm(name, place, startTime, endTime, type);
    }
}

void OpenNew::diffDaysWarning()
{
    QMessageBox messageBox(this);
    messageBox.setText("不能添加跨天事件！");
    QAbstractButton *confirmBt = messageBox.addButton(QMessageBox::Ok);
    messageBox.exec();
    connect(confirmBt, SIGNAL(clicked(bool)), this, SLOT(close()));
}

