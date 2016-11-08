#include "opennew.h"

//QList<Event>* Event::mylist;
//QList<Event>* Event::yourlist;


OpenNew::OpenNew(QWidget* parent):QDialog(parent)
{
    setWindowTitle("New");
}

void OpenNew::setinit()
{
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
    dateEdit->setMinimumDate(QDate::currentDate());
    dateEdit->setMaximumDate(QDate::currentDate().addDays(365));
    dateEdit->setDisplayFormat("yyyy.MM.dd");
    dateEdit->setGeometry(20,105,150,25);

//重复日期

    start1->setText("从");
    start1->setGeometry(QRect(20,108,20,20));
    start1->hide();

    startdate->setMinimumDate(QDate::currentDate());
    startdate->setMaximumDate(QDate::currentDate().addDays(365));
    startdate->setDisplayFormat("yyyy.MM.dd");
    startdate->setGeometry(40,105,150,25);
    startdate->hide();

    end1->setText("至");
    end1->setGeometry(QRect(200,108,20,20));
    end1->hide();

    enddate->setMinimumDate(QDate::currentDate());
    enddate->setMaximumDate(QDate::currentDate().addDays(365));
    enddate->setDisplayFormat("yyyy.MM.dd");
    enddate->setGeometry(220,105,150,25);
    enddate->hide();

//时间
    QLabel* start2 = new QLabel(this);
    start2->setText("从");
    start2->setGeometry(QRect(20,143,20,20));

    starttime->setMinimumTime(QTime::currentTime().addSecs(-3600*24));
    starttime->setMaximumTime(QTime::currentTime().addSecs(3600*24));
    starttime->setDisplayFormat("HH:mm:ss");
    starttime->setGeometry(40,140,150,25);

    QLabel* end2 = new QLabel(this);
    end2->setText("至");
    end2->setGeometry(QRect(200,143,20,20));

    endtime->setMinimumTime(QTime::currentTime().addSecs(-3600*24));
    endtime->setMaximumTime(QTime::currentTime().addSecs(3600*24));
    endtime->setDisplayFormat("HH:mm:ss");
    endtime->setGeometry(220,140,150,25);

//week选项
    QString weekStrings[7] = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
    QButtonGroup *weekdays = new QButtonGroup;
    for(int i=0; i<7; i++)
    {
        QCheckBox* weekday = new QCheckBox(weekStrings[i], this);
        weekday->setGeometry(20+50*i,180,50,20);
        weekdays->addButton(weekday);

    }

    QPushButton* addButton = new QPushButton(this);
    addButton->setText("添加");
    addButton->setGeometry(QRect(300,210,40,20));
    addButton->setStyleSheet("QPushButton {color: black;}");

    QObject::connect(timechoise, SIGNAL(buttonPressed(int)), this, SLOT(TimeChoose(int)));
    QObject::connect(addButton, SIGNAL(clicked(bool)), this, SLOT(send()));
    QObject::connect(this, SIGNAL(trans(QString, QString, QDateTime, QDateTime, int)), this, SLOT(addNewEvent(QString, QString, QDateTime, QDateTime, int)));

}

void OpenNew::TimeChoose(int id)
{

    if(id==1) //单次事件
    {
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
        startdate->show();
        enddate->show();
        start1->show();
        end1->show();
    }

}

//void OpenNew::addNewEvent(QString name, QString place, QDateTime starttime, QDateTime endtime, int type)
//{
//    Event *event = new Event(name, place, starttime, endtime, type);
//    Event::mylist->append(*event);
//    DB::query.exec("select * from myevent where name = sleep");
//    if (DB::query.next())
//    {
//         qDebug()<< DB::query.value(0).toInt()<<"\n";
//         qDebug()<< DB::query.value(1).toString()<<"\n";
//         qDebug()<< DB::query.value(2).toString()<<"\n";
//         qDebug()<< DB::query.value(3).toDateTime()<<"\n";
//         qDebug()<< DB::query.value(4).toDateTime()<<"\n";
//         qDebug()<< DB::query.value(5).toInt()<<"\n";
//     }

//}


