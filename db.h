#ifndef DB_H
#define DB_H

#include <QString>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QDebug>
#include <QSqlError>
class DB
{
public:
    DB();
    QSqlDatabase db;
    QSqlQuery query;
    void addEvent(QString name, QString place, QDateTime startTime, QDateTime endTime, int type);
    void dropDB();
    QSqlQuery readEvent();
};

#endif // DB_H
