#include "db.h"

DB::DB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/my.db");
    if (!db.open())
       {
//          qDebug() << "Error: connection with database fail";
       }
       else
       {
//          qDebug() << "Database: connection ok";
       }
    query = QSqlQuery(db);
    query.exec("CREATE TABLE IF NOT EXISTS event (id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name NVARCHAR(20) NOT NULL,"
               "place NVARCHAR(20) NOT NULL,"
               "starttime NVARCHAR(50) NOT NULL,"
               "endtime NVARCHAR(50) NOT NULL,"
               "type INTEGER NOT NULL);");
        qDebug()<<query.lastError();
}

void DB::dropDB() {
    query = QSqlQuery(db);
    query.exec("DROP TABLE IF EXISTS event;");
}

void DB::addEvent(QString name, QString place, QDateTime startTime, QDateTime endTime, int type)
{
    query = QSqlQuery(db);
    query.prepare("insert into event (name, place, starttime, endtime, type) values(:name, :place, :start, :end, :type);");
    query.bindValue(":name", name);
    query.bindValue(":place", place);
    query.bindValue(":start", startTime.toString());
    query.bindValue(":end", endTime.toString());
    query.bindValue(":type", type);
    bool success = query.exec();
    if (!success) {
        qDebug()<<query.lastError();
    }
}

QSqlQuery DB::readEvent() {
    query = QSqlQuery(db);
    query.exec("SELECT * FROM event;");
    qDebug()<<query.lastError();
    return query;
}
