#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Agenda"));
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

    //add datetime
    QLabel *label = new QLabel(this);
    QDateTime curr_time = QDateTime::currentDateTime();
    QString s = curr_time.toString(Qt::LocalDate);
    label->setText(s);
    label->setAlignment(Qt::AlignCenter);
    label->setGeometry(QRect(2,20,150,50));

}

