#include "connection.h"

connection::connection(){}
bool connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("Source_Projet2A");
db.setUserName("Amen");
db.setPassword("Esprit2024");

if (db.open()) test=true;
return test;
}
void connection::closeconnection(){db.close();}

