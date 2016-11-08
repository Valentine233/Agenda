#include "event.h"

Event::Event(QString name, QString place, QDateTime starttime, QDateTime endtime, int type)
{
    eventName = name;
    eventPlace = place;
    eventStart = starttime;
    eventEnd = endtime;
    //eventStart = starttime.toString("yyyy.MM.dd HH:mm:ss");
    //eventEnd = endtime.toString("yyyy.MM.dd HH:mm:ss");
    eventType = type;
    //addtoCalendar(eventName,eventPlace,eventStart,eventEnd,eventType);

}


void Event::paintEvent(QPaintEvent *)
{
    int i;
    QDateTime curr_time = QDateTime::currentDateTime().addDays(7*MainWindow::offset);
    QString weekStrings[7] = {"周一","周二","周三","周四","周五","周六","周日"};
    QString weekCurr = curr_time.toString("ddd");
    QString weekStart = eventStart.toString("ddd");

    //int starthour = starttime.toString("HH").toInt();
    //int startmin = starttime.toString("mm").toInt();
    int startminute = 60*eventStart.toString("HH").toInt() + eventStart.toString("mm").toInt();
    //int endhour = endtime.toString("HH").toInt();
    //int endmin = endtime.toString("mm").toInt();
    int endminute = 60*eventEnd.toString("HH").toInt() + eventEnd.toString("mm").toInt();



    for(i=0; i<7; i++)
    {
        if(weekCurr == weekStrings[i])
            break;
    }
    if(eventStart.date()<curr_time.addDays(-i).date()) //previous date
    {
        MainWindow::backwards();
        while(eventStart.date()<curr_time.addDays(-i).date())
        {
            MainWindow::backwards();
        }
    }
    else if(eventStart.date()>curr_time.addDays(6-i).date()) //following date
    {
        MainWindow::forward();
        while(eventStart.date()>curr_time.addDays(6-i).date())
        {
            MainWindow::forward();
        }
    }
    for(int j=0; j<7; j++)
    {
        if(weekStart == weekStrings[j])
        {
//            QPixmap myPixmap(100, 100);

            QPainter painter;
            painter.setPen(QPen(Qt::blue,4,Qt::DashLine));//设置画笔形式
            painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));//设置画刷形式
            painter.drawRect(50+100*j,100+480*startminute/(24*60),50+eventType*50,480*(endminute-startminute)/(24*60));
            //emit updateEvent(50+100*j,100+480*startminute/(24*60),50+type*50,480*(endminute-startminute)/(24*60));
            //painter->drawRect(50+100*j,100+480*startminute/(24*60),50+type*50,480*(endminute-startminute)/(24*60));
        }
    }
    //update(50+100*j,100+480*startminute/(24*60),50+type*50,480*(endminute-startminute)/(24*60));

}


