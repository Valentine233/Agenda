#ifndef DB_H
#define DB_H


class DB
{
public:
    DB();
    void addEvent();
private:
    static QSqlDatabase db;
};

#endif // DB_H
