#include "mainwindow.h"

QFile MyEventList("/Users/liaoxuan/QtProjet/Agenda/MyEventList.txt");
QFile YourEventList("/Users/liaoxuan/QtProjet/Agenda/YourEventList.txt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    QTextStream MyEvent(&MyEventList);
//    QTextStream YourEvent(&YourEventList);
    ui->setupUi(this);
    setinit();
    setWindowStyle();
    setWindowTitle(tr("Agenda"));
    db = new DB();
    loadFromDB();
//    db->dropDB();
    offset = 0;
    refreshAgenda(offset);
    // trans: an new special event is created
    QObject::connect(this, SIGNAL(openNewSignal(QMouseEvent*)), this, SLOT(openSpecialNew(QMouseEvent*)));
    writeToFile();
    readFromFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setinit()
{
    // create a new general event
    QPushButton *create = new QPushButton ( "新事件", this);
    create->setGeometry(800,100,100,40);
    connect(create, SIGNAL(clicked(bool)), this, SLOT(openGeneralNew()));

    // to next week
    QPushButton *forward_button = new QPushButton ( ">", this);
    forward_button->setGeometry(750,60,20,20);
    connect(forward_button, SIGNAL(clicked(bool)), this, SLOT(forward()));
    // to last week
    QPushButton *backwards_button = new QPushButton ( "<", this);
    backwards_button->setGeometry(30,60,20,20);
    connect(backwards_button, SIGNAL(clicked(bool)), this, SLOT(backwards()));
    // back to the current week
    QPushButton *current = new QPushButton ( "今天", this);
    current->setGeometry(QRect(80,25,65,30));
    connect(current, SIGNAL(clicked(bool)), this, SLOT(currentTime()));

    int i;
    //add the vertical time zone
    for(i=0; i<13; i++)
    {
        QString s = QString::number(2*i);
        QLabel *label = new QLabel(this);
        label->setText(s);
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

    // Initialize the event list, by reading from db
    list = new QList<Event*>();
    //yourlist = new QList<Event*>();

    // Read settings
    Event::defaultDuration = 60;
}

void MainWindow::setWindowStyle() {
    this->setStyleSheet("MainWindow {background-color:#fff;}");
    //this->setStyleSheet("MainWindow {background-color:#fff;} QLabel {color:#888;}");
    this->setFixedSize(rightX+250,bottomY+40);

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);

    int i;
    QLine hlines[13];
    for(i=0; i<13; i++)
    {
        hlines[i] = QLine(leftX,topY+gridHight*i,rightX,topY+gridHight*i);
    }
    QLine vlines[8];
    for(i=0; i<8; i++)
    {
        vlines[i] = QLine(leftX+2*gridWidth*i,topY,leftX+2*gridWidth*i,bottomY);
    }
    QLine divide[7];
    for(i=0; i<7; i++)
    {
        divide[i] = QLine(leftX+gridWidth*(2*i+1),topY,leftX+gridWidth*(2*i+1),bottomY);
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

QLabel* MainWindow::addEventUI(Event *event)
{
    QString weekStrings[7] = {"周一","周二","周三","周四","周五","周六","周日"};
    QString weekStart = event->eventStart.toString("ddd");
    int startminute = 60*event->eventStart.toString("HH").toInt() + event->eventStart.toString("mm").toInt();
    int endminute = 60*event->eventEnd.toString("HH").toInt() + event->eventEnd.toString("mm").toInt();

    for(int j=0; j<7; j++)
    {
        if(weekStart == weekStrings[j])
        {
            if(event->eventType == 0)
            {
                MyEventLabel* eventRect = new MyEventLabel(this, event);
                eventRect->setGeometry(50+100*j,100+480*startminute/(24*60),50,480*(endminute-startminute)/(24*60));
                eventRect->setText(event->eventName+"\n"+event->eventPlace);
                event->eventUI = eventRect;
                return eventRect;
            }
            else if(event->eventType == 1)
            {
                YourEventLabel* eventRect = new YourEventLabel(this, event);
                eventRect->setGeometry(100+100*j,100+480*startminute/(24*60),50,480*(endminute-startminute)/(24*60));
                eventRect->setText(event->eventName+"\n"+event->eventPlace);
                event->eventUI = eventRect;
                return eventRect;
            }
        }
    }
}

void MainWindow::removeEventUI()
{
    for(int k = 0; k < list->size(); k++)
    {
        if (list->at(k)->eventUI != NULL) {
            delete list->at(k)->eventUI;
            list->at(k)->eventUI = NULL;
        }
    }
}

void MainWindow::refreshAgenda(int _offset)
{
    removeEventUI();
    offset = _offset;
    // 是当前时间 + week的偏移量的结果
    curr_time = QDateTime::currentDateTime().addDays(7*offset);
    // QString weekStrings[7] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
    QString weekStrings[7] = {"周一","周二","周三","周四","周五","周六","周日"};
    //add EventUI
    for(int k = 0; k < list->size(); k++)
    {
        QDate curr_date = QDate::currentDate();
        int offset_k = (curr_date.addDays(-1*curr_date.dayOfWeek()).daysTo(list->at(k)->eventStart.date().addDays(-1 * list->at(k)->eventStart.date().dayOfWeek()))) / 7;
        if (offset == offset_k) {
             //event is in this week
            addEventUI(list->at(k));
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

void MainWindow::forward()
{
    refreshAgenda(offset+1);
}

void MainWindow::backwards()
{
    refreshAgenda(offset-1);
}

void MainWindow::currentTime()
{
    refreshAgenda(0);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

    if( event->buttons() == Qt::LeftButton && event->x() > leftX && event->x() < rightX && event->y()>topY && event->y()<bottomY)
    {
        emit openNewSignal(event);
    }
}

void MainWindow::openSpecialNew(QMouseEvent *event)
{
    OpenNew opennew(this);
    opennew.setGeometry(event->globalX()+50,event->globalY()-30,400,240);
    opennew.setInit(event->x(), event->y());
    opennew.exec();
}

void MainWindow::openGeneralNew()
{
    OpenNew opennew(this);
    opennew.setGeometry(leftX+380,topY+160,400,240);
    opennew.setInit(-1,-1);
    opennew.exec();
}

void MainWindow::turnToEventTime(Event *event)
{
    QDate curr_date = QDate::currentDate();
    offset = (curr_date.addDays(-1*curr_date.dayOfWeek()).daysTo(event->eventStart.date().addDays(-1 * event->eventStart.date().dayOfWeek()))) / 7;
    refreshAgenda(offset);
}

void MainWindow::createNewEvent(QString name, QString place, QDateTime starttime, QDateTime endtime, int type)
{
    Event *event = new Event(name,place,starttime,endtime,type,this);
    list->append(event);
    db->addEvent(name,place,starttime,endtime,type);
    turnToEventTime(event);
}

void MainWindow::editEvent(QString name, QString place, QDateTime starttime, QDateTime endtime, int type, QString nameOld, QString placeOld, QDateTime startOld, QDateTime endOld)
{
    for(int k = 0; k < list->size(); k++)
    {
        if (list->at(k)->eventName == nameOld && list->at(k)->eventPlace == placeOld && list->at(k)->eventStart == startOld
                && list->at(k)->eventEnd == endOld && list->at(k)->eventType == 0)
        {
            list->at(k)->eventName = name;
            list->at(k)->eventPlace = place;
            list->at(k)->eventStart = starttime;
            list->at(k)->eventEnd = endtime;
            refreshAgenda(offset);

            //从数据库里更新
            db->updateEvent(name, place, starttime, endtime, type, nameOld, placeOld, startOld, endOld);
        }
    }
}

void MainWindow::deleteEvent(QString name, QString place, QDateTime starttime, QDateTime endtime, int type)
{
    for(int k = 0; k < list->size(); k++)
    {
        if (list->at(k)->eventName == name && list->at(k)->eventPlace == place && list->at(k)->eventStart == starttime
                && list->at(k)->eventEnd == endtime && list->at(k)->eventType == type)
        {
            Event* _event = list->at(k);
            list->removeAt(k);
            delete _event->eventUI;
            delete _event;
            refreshAgenda(offset);

            //从数据库删除
            db->deleteEvent(name, place, starttime, endtime, type);
        }
    }
}

void MainWindow::loadFromDB()
{

    QSqlQuery query = db->readEvent();
    QSqlRecord record = query.record();
    int idName = record.indexOf("name");
    int idPlace = record.indexOf("place");
    int idStart = record.indexOf("starttime");
    int idEnd = record.indexOf("endtime");
    int idType = record.indexOf("type");
    while (query.next())
    {
       QString name = query.value(idName).toString();
       QString place = query.value(idPlace).toString();
       QDateTime starttime = QDateTime::fromString(query.value(idStart).toString());
       QDateTime endtime = QDateTime::fromString(query.value(idEnd).toString());
       int type = query.value(idType).toString().toInt();
       Event *event = new Event(name,place,starttime,endtime,type,this);
       list->append(event);
    }
}

void MainWindow::eventsLoseFocus()
{
    for(int k = 0; k < list->size(); k++)
    {
        if (list->at(k)->eventUI != NULL && list->at(k)->eventType == 0) {
            list->at(k)->eventUI->setStyleSheet("background-color: rgba(34, 24, 245, 50);text-align: center; ");
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    eventsLoseFocus();
    event->accept();
}

void MainWindow::writeToFile() //传出我的文件时
{
    //未实现抹去MyEventList文件内容！
    if (!MyEventList.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"WriteError: Can't open the file!\n";
        return;
    }
    QTextStream out(&MyEventList);
    QSqlQuery query =  db->readAllMyEvent();
    QSqlRecord record = query.record();
    int idName = record.indexOf("name");
    int idPlace = record.indexOf("place");
    int idStart = record.indexOf("starttime");
    int idEnd = record.indexOf("endtime");
    int idType = record.indexOf("type");
    while (query.next())
    {
       QString name = query.value(idName).toString();
       QString place = query.value(idPlace).toString();
       QDateTime starttime = QDateTime::fromString(query.value(idStart).toString());
       QDateTime endtime = QDateTime::fromString(query.value(idEnd).toString());
       int type = query.value(idType).toString().toInt();
       QString start = starttime.toString("yyyy/MM/dd HH:mm");
       QString end = endtime.toString("yyyy/MM/dd HH:mm");
       out<<name<<",;"<<place<<",;"<<start<<",;"<<end<<",;"<<type<<"\n";
    }
}

void MainWindow::readFromFile() //接收对方文件时
{
    //未实现替换现有YourEventList文件！
    db->deleteAllYourEvent();
    if(!YourEventList.open(QIODevice::ReadWrite | QIODevice::Text))
    {
         qDebug()<<"ReadError: Can't open the file!\n";
         return;
    }
    while(!YourEventList.atEnd()) {
        QByteArray line = YourEventList.readLine();
        QString str(line);
        int i=0;
        int flag=0;
        QString Name, Place, Start, End, Type;
        while(str[i]!='\x0')
        {
            while(str[i]!=',' || str[i+1]!=';')
            {
                switch (flag) {
                case 0: //0:eventName
                    Name += str[i];
                    break;
                case 1: //1:eventPlace
                    Place += str[i];
                    break;
                case 2: //2:eventStart
                    Start += str[i];
                    break;
                case 3: //3:eventEnd
                    End += str[i];
                    break;
                case 4: //4:eventType
                    Type += str[i];
                    break;
                default:
                    break;
                }
                if(str[i+1] == '\x0' || str[i+1] == '\n')
                    break;
                i++;
            }
            if(flag!=4)
                i++;
            flag++;
            i++;
        }
        QDateTime starttime = QDateTime::fromString(Start, "yyyy/MM/dd HH:mm");
        QDateTime endtime = QDateTime::fromString(End, "yyyy/MM/dd HH:mm");
        if(Type != "0") //对于对方来说是0事件
        {
            qDebug() << "type=" <<Type << "error";
        }
        int type = 1; //储存为1事件
        createNewEvent(Name, Place, starttime, endtime, type);
    }
}
