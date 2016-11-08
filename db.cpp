#include "db.h"

QSqlQuery DB::query;

DB::DB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/tmp/my.db");
    db.open();
    QSqlQuery query;
    query = QSqlQuery(db);
    query.exec("CREATE TABLE IF NOT EXISTS myevent (id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name NVARCHAR(20) NOT NULL,"
               "place NVARCHAR(20) NOT NULL,"
               "starttime DATETIME NOT NULL,"
               "endtime DATETIME NOT NULL");

}

void DB::AddEvent(QString name, QString place, QString starttime, QString endtime)
{

    query.exec(QString("insert into myevent values(nulll,'%1','%2',to_date('%3','yyyy.MM.dd HH:mm:ss'),"
                       "to_date('%4','yyyy.MM.dd HH:mm:ss')").arg(name,place,starttime,endtime));

}

