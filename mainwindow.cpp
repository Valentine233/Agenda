#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QDateTime>
#include <QPushButton>
#include <QDialog>
#include <createnew.h>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Agenda"));
    offset = 0;
    time();
    button();
    QObject::connect(ct, SIGNAL(trans(QString,QString,QString)), this, SLOT(add(QString,QString,QString)));

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

void MainWindow::time()
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

    //add current time
    QLabel *label = new QLabel(this);
    QDateTime currTime = QDateTime::currentDateTime();
    QString month = currTime.toLocalTime().toString("MMM");
//    QString s = curr_time.toString(Qt::LocalDate);
    label->setText(month);
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(QRect(2,20,150,50));
//    QString weekStrings[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    QString weekStrings[7] = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
    QLabel *weekLabels[7];
    QLabel *dayLabels[7];
    int currI = -1;
    for (int i = 0; i<7; i++) {
        // Week information
        QLabel *weekLabel = new QLabel(this);
        weekLabel->setText(weekStrings[i]);
        weekLabel->setAlignment(Qt::AlignCenter);
        weekLabel->setGeometry(QRect(i*100+50,30,100,100));
        weekLabels[i] = weekLabel;
        qDebug() << currTime.toString("ddd");
        if (weekStrings[i] == currTime.toString("ddd")) {
            currI = i;
            QLabel * dayLabel = new QLabel(this);
            dayLabel->setText(currTime.toString("d"));
            dayLabel->setAlignment(Qt::AlignCenter);
            dayLabel->setGeometry(QRect(i*100+50,40,100,100));
            dayLabels[i] = dayLabel;
            for (int j = 0;j<i;j++) {
                qDebug() << currTime.addDays(-i+j).toString("d");
                QLabel * dayLabel = new QLabel(this);
                dayLabel->setText(currTime.addDays(-i+j).toString("d"));
                dayLabel->setAlignment(Qt::AlignCenter);
                dayLabel->setGeometry(QRect(j*100+50,40,100,100));
                dayLabels[j] = dayLabel;
            }
            for (int j = 6; j>i;j--) {
                qDebug() << j;
                QLabel * dayLabel = new QLabel(this);
                dayLabel->setText(currTime.addDays(j-i).toString("d"));
                dayLabel->setAlignment(Qt::AlignCenter);
                dayLabel->setGeometry(QRect(j*100+50,40,100,100));
                dayLabels[j] = dayLabel;
            }
        }

        // Day information



    }
}

void MainWindow::button()
{
    QPushButton *create = new QPushButton ( "&Create", this);
    create->setGeometry(800,100,100,40);
    connect(create, SIGNAL(clicked(bool)), this, SLOT(open()));
}

void MainWindow::open()
{
    ct->setinit();
    ct->setModal(false);
    ct->show();
}

void MainWindow::add(QString day, QString time1, QString time2)
{
//    switch (day) {
//    case "Monday"||"monday":
//        QLabel *time_f = new QLabel(this);
//        time_f->setGeometry(QRect(20,250,100,30));
//        time_f->setText(day+time1+time2);
//        break;
//    default:
//        break;
//    }
//    QLabel *time_c = new QLabel(this);
//    time_c->setGeometry(QRect(20,250,100,30));
//    time_c->setText(day+time1+time2);

}







