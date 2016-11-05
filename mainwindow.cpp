#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Agenda"));
    //settime();
    setinit();

    offset = 0;
    time(offset);
    //button();

    connect(ct, SIGNAL(trans(QString,QString,QString)), this, SLOT(add(QString,QString,QString)));
    connect(this, SIGNAL(openNewSignal(QMouseEvent*)), this, SLOT(openNew(QMouseEvent*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
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

    painter.setPen(Qt::gray);
    painter.drawLines(hlines, 13);
    painter.drawLines(vlines, 8);

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setBrush(Qt::lightGray);
    painter.setPen(pen);
    painter.drawLines(divide, 7);

}


void MainWindow::time(int offset)
{
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

//    QDateTime curr_time = QDateTime::currentDateTime();

//    // QString weekStrings[7] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
//    QString weekStrings[7] = {"周一","周二","周三","周四","周五","周六","周日"};

//    //week information
//    for(int i=0; i<7; i++)
//    {
//        QLabel *weekLabel = new QLabel(this);
//        weekLabel->setText(weekStrings[i]);
//        weekLabel->setAlignment(Qt::AlignCenter);
//        weekLabel->setGeometry(QRect(50+100*i, 25, 100, 100));
//        weekLabels[i] = weekLabel;
//        if( weekStrings[i] == curr_time.toString("ddd") )
//        {
//            QPalette pe;
//            pe.setColor(QPalette::WindowText,Qt::red);
//            weekLabels[i]->setPalette(pe);

//            //month information
//            month->setText(curr_time.addDays(-i).toString("M"));
//            QFont font("Times", 25);
//            month->setFont(font);
//            month->setAlignment(Qt::AlignCenter);
//            month->setGeometry(QRect(2,20,100,50));

//            for( int j=0; j<7; j++)
//            {
//                QLabel *dayLabel = new QLabel(this);
//                dayLabel->setText(curr_time.addDays(j-i).toString("d"));
//                dayLabel->setAlignment(Qt::AlignCenter);
//                dayLabel->setGeometry(QRect(50+100*j, 40, 100, 100));
//                if(j==i)
//                    dayLabel->setPalette(pe);
//                dayLabels[j] = dayLabel;
//            }
//        }

    //add current time
    QLabel *label = new QLabel(this);
    QDateTime currTime = QDateTime::currentDateTime();
    // Add month information
    QString month = currTime.toLocalTime().addDays(7*offset).toString("MMM");
    label->setText(month);
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(QRect(2,20,150,50));
//    QString weekStrings[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    QString weekStrings[7] = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
    QLabel *weekLabels[7];
    QLabel *dayLabels[7];
    for (int i = 0; i<7; i++) {
        // Week information
        QLabel *weekLabel = new QLabel(this);
        weekLabel->setText(weekStrings[i]);
        weekLabel->setAlignment(Qt::AlignCenter);
        weekLabel->setGeometry(QRect(i*100+50,20,100,100));
        weekLabels[i] = weekLabel;
        if (weekStrings[i] == currTime.toString("ddd")) {
            // Day information
            for (int j = 0;j<7;j++) {
                QLabel * dayLabel = new QLabel(this);
                dayLabel->setText(currTime.addDays(-i+j).toString("d"));
                dayLabel->setAlignment(Qt::AlignCenter);
                dayLabel->setGeometry(QRect(j*100+50,40,100,100));
                dayLabels[j] = dayLabel;
            }
        }

    }
}

void MainWindow::setinit()
{
    QPushButton *create = new QPushButton ( "&Create", this);
    create->setGeometry(800,100,100,40);
    connect(create, SIGNAL(clicked(bool)), this, SLOT(open()));
    QPushButton *forward_button = new QPushButton ( ">", this);
    forward_button->setGeometry(750,60,20,20);
    connect(forward_button, SIGNAL(clicked(bool)), this, SLOT(forward()));
    QPushButton *backwards_button = new QPushButton ( "<", this);
    backwards_button->setGeometry(30,60,20,20);
    connect(backwards_button, SIGNAL(clicked(bool)), this, SLOT(backwards()));
    QPushButton *current = new QPushButton ( "&Today", this);
    current->setGeometry(QRect(100,20,65,50));
    connect(current, SIGNAL(clicked(bool)), this, SLOT(currenttime()));
}

void MainWindow::forward()
{
    qDebug() << "enter forward";
    QDateTime time;
    time = QDateTime::fromString(month->text()+'-'+dayLabels[0]->text(), "M-d");
    //qDebug() << dayLabels[0]->text();
    month->text() = time.addDays(7).toString("M");
    //qDebug() << month->text();
    for(int i=0; i<7; i++)
    {
        dayLabels[i]->text() = time.addDays(7+i).toString("d");
        qDebug() << dayLabels[i]->text();
    }
}

void MainWindow::backwards()
{
    qDebug() << "enter backwards";
    QDateTime time;
    time = QDateTime::fromString(month->text()+'-'+dayLabels[0]->text(), "M-d");
    month->text() = time.addDays(-7).toString("M");
    for(int i=0; i<7; i++)
    {
        dayLabels[i]->text() = time.addDays(-7+i).toString("d");
        qDebug() << dayLabels[i]->text();
    }
}

void MainWindow::currenttime()
{
    qDebug() << "go back";
    QDateTime curr_time = QDateTime::currentDateTime();
    for(int i=0; i<7; i++)
    {
        if( weekLabels[i]->text() == curr_time.toString("ddd") )
        {
            QPalette pe;
            pe.setColor(QPalette::WindowText,Qt::red);
            weekLabels[i]->setPalette(pe);

            month->setText(curr_time.addDays(-i).toString("M"));

            for( int j=0; j<7; j++)
            {
                dayLabels[j]->setText(curr_time.addDays(j-i).toString("d"));
                if(j==i)
                    dayLabels[j]->setPalette(pe);
            }
        }
    }

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






