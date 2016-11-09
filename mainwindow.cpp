#include "mainwindow.h"

QFile MyEventList("/Users/liaoxuan/QtProjet/Agenda/MyEventList.txt");
QFile YourEventList("/Users/liaoxuan/QtProjet/Agenda/YourEventList.txt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextStream MyEvent(&MyEventList);
    QTextStream YourEvent(&YourEventList);
    ui->setupUi(this);
    setinit();
    setWindowTitle(tr("Agenda"));
    offset = 0;
    setTime(offset);
    QObject::connect(ct, SIGNAL(trans(QString,QString,QString)), this, SLOT(add(QString,QString,QString)));
    QObject::connect(this, SIGNAL(openNewSignal(QMouseEvent*)), this, SLOT(openNew(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);

    int i;
    QLine hlines[13];
    for(i=0; i<13; i++)
    {
        hlines[i] = QLine(50,100+40*i,750,100+40*i);
    }
    QLine vlines[8];
    for(i=0; i<8; i++)
    {
        vlines[i] = QLine(50+100*i,100,50+100*i,580);
    }
    QLine divide[7];
    for(i=0; i<7; i++)
    {
        divide[i] = QLine(100+100*i,100,100+100*i,580);
    }

    painter->setPen(Qt::gray);
    painter->drawLines(hlines, 13);
    painter->drawLines(vlines, 8);

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setBrush(Qt::lightGray);
    painter->setPen(pen);
    painter->drawLines(divide, 7);

    painter->end();
}

void MainWindow::addEventUI(Event *event)
{
    QString weekStrings[7] = {"周一","周二","周三","周四","周五","周六","周日"};
    QString weekStart = event->eventStart.toString("ddd");

    int startminute = 60*event->eventStart.toString("HH").toInt() + event->eventStart.toString("mm").toInt();
    int endminute = 60*event->eventEnd.toString("HH").toInt() + event->eventEnd.toString("mm").toInt();

    for(int j=0; j<7; j++)
    {
        if(weekStart == weekStrings[j])
        {

            QLabel *eventRect = new QLabel(this);
            eventRect->setGeometry(50+100*j,100+480*startminute/(24*60),50+event->eventType*50,480*(endminute-startminute)/(24*60));
            eventRect->setStyleSheet("background-color: rgba(34, 24, 245, 50);");
            eventRect->setText(event->eventName+"\n"+event->eventPlace);
            eventRect->setAlignment(Qt::AlignCenter);
            eventRect->show();
        }
    }
}

void MainWindow::setTime(int _offset)
{
    offset = _offset;
    // 是当前时间 + week的偏移量的结果
    curr_time = QDateTime::currentDateTime().addDays(7*offset);
    // QString weekStrings[7] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    QString weekStrings[7] = {"周一","周二","周三","周四","周五","周六","周日"};
    QString weekCurr = curr_time.toString("ddd");

    //add EventUI
    int i;
    //QList<Event> *list = mylist;
    QList<Event>::Iterator e;
    for(e=mylist->begin(); e!=mylist->end(); e++)
    {
        for(i=0; i<7; i++)
        {
            if(weekCurr == weekStrings[i])
                break;
        }
        if(e->eventStart.date()>=curr_time.addDays(-i).date() && e->eventStart.date()<=curr_time.addDays(6-i).date()) //event is in this week
        {
            addEventUI(e);
        }
    }

    //week information
    for(int i=0; i<7; i++)
    {
        QLabel *weekLabel = weekLabels[i];
        weekLabel->setAlignment(Qt::AlignCenter);
        weekLabel->setText(weekStrings[i]);
        weekLabel->setGeometry(QRect(77+100*i, 45, 40, 30));
        if( weekStrings[i] == curr_time.toString("ddd") )
        {
            QPalette pe_defalt;
            pe_defalt.setColor(QPalette::WindowText,Qt::black);
            QPalette pe;
            pe.setColor(QPalette::WindowText,Qt::red);

            //month information
            month->setText(curr_time.addDays(-i).toString("M"));


            for( int j=0; j<7; j++)
            {

                QLabel *dayLabel = dayLabels[j];
                dayLabel->setText(curr_time.addDays(j-i).toString("d"));
                dayLabel->setAlignment(Qt::AlignCenter);
                dayLabel->setGeometry(QRect(77+100*j, 70, 40, 15));
                if (j==i && offset!=0) {
                    dayLabel->setPalette(pe_defalt);
                    weekLabel->setPalette(pe_defalt);
                }
                if(j==i && offset == 0) {
                    dayLabel->setPalette(pe);
                    weekLabel->setPalette(pe);
                }

            }
        }
    }
}


void MainWindow::setinit()
{
    QPushButton *create = new QPushButton ( "&Create", this);
    create->setGeometry(800,100,100,40);
    connect(create, SIGNAL(clicked(bool)), this, SLOT(open()));

    // to next week
    QPushButton *forward_button = new QPushButton ( ">", this);
    forward_button->setGeometry(750,60,20,20);
    connect(forward_button, SIGNAL(clicked(bool)), this, SLOT(forward()));
    // to last week
    QPushButton *backwards_button = new QPushButton ( "<", this);
    backwards_button->setGeometry(30,60,20,20);
    connect(backwards_button, SIGNAL(clicked(bool)), this, SLOT(backwards()));
    // back to the current week
    QPushButton *current = new QPushButton ( "&Today", this);
    current->setGeometry(QRect(80,25,65,30));
    connect(current, SIGNAL(clicked(bool)), this, SLOT(currenttime()));

    int i;
    //add the vertical time zone
    for(i=0; i<13; i++)
    {
        QString s = QString::number(2*i);
        QLabel *label = new QLabel(this);
        label->setText(s+":00");
        label->setAlignment(Qt::AlignCenter);
        label->setGeometry(QRect(0, 80+40*i, 50, 40));
    }

    QFont font("Times", 25);
    month->setFont(font);
    month->setAlignment(Qt::AlignCenter);
    month->setGeometry(QRect(2,20,100,50));
    for (int i=0; i<7; i++) {

        QLabel *weekLabel = new QLabel(this);
        weekLabels[i] = weekLabel;
        QLabel *dayLabel = new QLabel(this);
        dayLabels[i] = dayLabel;
    }
}

void MainWindow::forward()
{
    setTime(offset+1);
}

void MainWindow::backwards()
{
    setTime(offset-1);
}

void MainWindow::currenttime()
{
    setTime(0);
}

void MainWindow::open()
{
    ct->setinit();
    ct->setModal(true);
    ct->show();
}

void MainWindow::add(QString day, QString time1, QString time2)
{
    QLabel *time_c = new QLabel(this);
    time_c->setGeometry(QRect(20,250,100,30));
    time_c->setText(day+time1+time2);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if( event->buttons() == Qt::LeftButton)
    {
        emit openNewSignal(event);
    }
}

void MainWindow::openNew(QMouseEvent *event)
{
    OpenNew opennew(this);
    opennew.setGeometry(event->globalX(),event->globalY(),400,240);
    opennew.setinit();
    opennew.exec();
}

void MainWindow::turnToEventTime(Event *event)
{
    int i;
    QString weekStrings[7] = {"周一","周二","周三","周四","周五","周六","周日"};
    QString weekCurr = curr_time.toString("ddd");


    for(i=0; i<7; i++)
    {
        if(weekCurr == weekStrings[i])
            break;
    }
    if(event->eventStart.date()<curr_time.addDays(-i).date()) //previous date
    {
        backwards();
        while(event->eventStart.date()<curr_time.addDays(-i).date())
        {
            backwards();
        }
    }
    else if(event->eventStart.date()>curr_time.addDays(6-i).date()) //following date
    {
        forward();
        while(event->eventStart.date()>curr_time.addDays(6-i).date())
        {
            forward();
        }
    }
}

void MainWindow::addtoEventList(QString name, QString place, QDateTime starttime, QDateTime endtime, int type)
{
    Event *event = new Event(name,place,starttime,endtime,type,this);
    mylist->append(*event);

    turnToEventTime(event);
    addEventUI(event);
}
