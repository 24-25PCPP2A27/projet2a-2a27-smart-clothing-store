#include "clients.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
#include <QSqlError>
#include <QMap>
#include <QSqlError>
#include <QDebug>
#include <QVariant>


// Constructor implementations should match the class name
Clients::Clients() : idcl(0), nom(""), prenom(""), adresse(""), email(""), telephone(""), status(""), anciennete(0) {}

Clients::Clients(int idcl, QString nom, QString prenom, QString adresse, QString email, QString telephone, QString status, int anciennete) {
    this->idcl = idcl;
    this->nom = nom;
    this->prenom = prenom;
    this->adresse = adresse;
    this->email = email;
    this->telephone = telephone;
    this->status = status;
    this->anciennete = anciennete;
}
// Method to add a client
bool Clients::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS (IDCL, NOM, PRENOM, ADRESSE, EMAIL, TELEPHONE, STATUS, ANCIENNETE) "
                  "VALUES (:IDCL, :NOM, :PRENOM, :ADRESSE, :EMAIL, :TELEPHONE, :STATUS, :ANCIENNETE)");
    query.bindValue(":IDCL", idcl);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":ADRESSE", adresse);
    query.bindValue(":EMAIL", email);
    query.bindValue(":TELEPHONE", telephone);
    query.bindValue(":STATUS", status);
    query.bindValue(":ANCIENNETE", anciennete);
    return query.exec();
}

// Method to display clients
QSqlQueryModel* Clients::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDCL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("STATUS"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ANCIENNETE"));
    return model;
}

// Method to delete a client
bool Clients::supprimer(int idcl) {
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENTS WHERE IDCL = :IDCL");
    query.bindValue(":IDCL", idcl);
    return query.exec();
}

// Method to modify client details
bool Clients::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE CLIENTS SET NOM = :NOM, PRENOM = :PRENOM, ADRESSE = :ADRESSE, "
                  "EMAIL = :EMAIL, TELEPHONE = :TELEPHONE, STATUS = :STATUS, ANCIENNETE = :ANCIENNETE "
                  "WHERE IDCL = :IDCL");
    query.bindValue(":IDCL", idcl);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":ADRESSE", adresse);
    query.bindValue(":EMAIL", email);
    query.bindValue(":TELEPHONE", telephone);
    query.bindValue(":STATUS", status);
    query.bindValue(":ANCIENNETE", anciennete);
    return query.exec();
}
QSqlQueryModel* Clients::trier(bool ordreAscendant)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // Construct the query to sort the suppliers by ANCIENNETE (seniority)
    QString queryStr;
    if (ordreAscendant) {
        queryStr = "SELECT IDCL, NOM, PRENOM, ADRESSE, EMAIL, TELEPHONE, STATUS, ANCIENNETE FROM CLIENTS ORDER BY ANCIENNETE ASC";
    } else {
        queryStr = "SELECT IDCL, NOM, PRENOM, ADRESSE, EMAIL, TELEPHONE, STATUS, ANCIENNETE FROM CLIENTS ORDER BY ANCIENNETE ASC";

    }

    // Set the query to the model
    model->setQuery(queryStr);

    // Set the headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDCL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("STATUS"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ANCIENNETE"));

    return model;
}
// Définition de la méthode rechercherParID
QSqlQueryModel* Clients::rechercheID(int idcl)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM clients WHERE idcl = :idcl");
    query.bindValue(":idcl", idcl);
    if (query.exec()) {
        model->setQuery(query);
    }
    return model;
}
QMap<QString, int> Clients::getStatistiquesByStatus()
{
    QMap<QString, int> stats;
    QSqlQuery query;

    // Query to get count of clients grouped by status
    query.prepare("SELECT status, COUNT(*) as count FROM clients GROUP BY status");

    if (!query.exec()) {
        qDebug() << "Error retrieving status statistics:" << query.lastError().text();
    } else {
        while (query.next()) {
            QString status = query.value("status").toString();
            int count = query.value("count").toInt();
            stats[status] = count;  // Store the status and count in the map
        }
    }

    return stats;
}


int Clients::calculerPointsFidelite(int clientId) {
    // Exemple de calcul basique : pourrait être basé sur des achats passés, etc.
    QSqlQuery query;
    query.prepare("SELECT points_base FROM clients WHERE idcl = :idcl");
    query.bindValue(":idcl", clientId);

    if (query.exec() && query.next()) {
        // Récupérer et retourner les points de base du client
        return query.value(0).toInt();
    }

    // En cas d'erreur, retourner 0
    return 0;
}

