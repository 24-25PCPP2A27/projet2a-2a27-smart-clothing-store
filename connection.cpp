#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données
db.setUserName("Mayssem");//inserer nom de l'utilisateur
db.setPassword("esprit4923");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
return  test;
}

void connection::closeConnection(){db.close();}
