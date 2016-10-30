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

    QLabel *label1 = new QLabel(this);
    label1->setText("Monday");
    label1->setAlignment(Qt::AlignCenter);
    label1->setGeometry(QRect(50, 30, 100, 100));

    QLabel *label2 = new QLabel(this);
    label2->setText("Tuesday");
    label2->setAlignment(Qt::AlignCenter);
    label2->setGeometry(QRect(150, 30, 100, 100));

    QLabel *label3 = new QLabel(this);
    label3->setText("Wednesday");
    label3->setAlignment(Qt::AlignCenter);
    label3->setGeometry(QRect(250, 30, 100, 100));

    QLabel *label4 = new QLabel(this);
    label4->setText("Thursday");
    label4->setAlignment(Qt::AlignCenter);
    label4->setGeometry(QRect(350, 30, 100, 100));

    QLabel *label5 = new QLabel(this);
    label5->setText("Friday");
    label5->setAlignment(Qt::AlignCenter);
    label5->setGeometry(QRect(450, 30, 100, 100));

    QLabel *label6 = new QLabel(this);
    label6->setText("Saturday");
    label6->setAlignment(Qt::AlignCenter);
    label6->setGeometry(QRect(550, 30, 100, 100));

    QLabel *label7 = new QLabel(this);
    label7->setText("Sunday");
    label7->setAlignment(Qt::AlignCenter);
    label7->setGeometry(QRect(650, 30, 100, 100));

    //add datetime
    QLabel *label = new QLabel(this);
    QDateTime curr_time = QDateTime::currentDateTime();
    QString s = curr_time.toString(Qt::LocalDate);
    label->setText(s);
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(QRect(2,20,150,50));

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
    switch (day) {
    case "Monday"||"monday":
        QLabel *time_f = new QLabel(this);
        time_f->setGeometry(QRect(20,250,100,30));
        time_f->setText(day+time1+time2);
        break;
    default:
        break;
    }
    QLabel *time_c = new QLabel(this);
    time_c->setGeometry(QRect(20,250,100,30));
    time_c->setText(day+time1+time2);

}







