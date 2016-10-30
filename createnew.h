#ifndef CREATENEW_H
#define CREATENEW_H

#include <QDialog>

class CreateNew : public QDialog
{
    Q_OBJECT

public:
    CreateNew();
    void setinit();

protected slots:
    void send()
    {
        emit trans(day, time1, time2);
    }

signals:
    void trans(QString day, QString time1, QString time2);

private:
    QString day;
    QString time1;
    QString time2;

};

#endif // CREATENEW_H
