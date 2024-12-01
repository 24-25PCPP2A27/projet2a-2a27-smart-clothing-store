#ifndef CONNECTIONARTICLES_H
#define CONNECTIONARTICLES_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class ConnectionArticles
{
    QSqlDatabase db;
public:
    ConnectionArticles();
    bool createconnect();
    void closeConnection();
};

#endif // CONNECTIONARTICLES_H
