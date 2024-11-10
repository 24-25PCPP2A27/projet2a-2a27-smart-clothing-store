#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class connection
{
    QSqlDatabase db;
public:
    connection();
    bool createconnect();
    void closeConnection();
};

#endif // CONNECTION_H
