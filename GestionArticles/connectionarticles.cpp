#include "connectionarticles.h"

ConnectionArticles::ConnectionArticles()
{

}

bool ConnectionArticles::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("Mayssem");
db.setPassword("esprit4923");

if (db.open()) test=true;
return  test;
}

void ConnectionArticles::closeConnection(){db.close();}
