#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("ilef1");//inserer nom de l'utilisateur
db.setPassword("ilef123");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





return  test;
}
