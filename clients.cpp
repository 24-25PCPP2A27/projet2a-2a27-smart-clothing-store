#include "clients.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
#include <QSqlError>
#include <QMap>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QDateTime>


// Constructor implementations should match the class name
Clients::Clients() : idcl(0), nom(""), prenom(""), adresse(""), email(""), telephone(""), status(""), anciennete(0), derniereActivite(QDateTime::currentDateTime()) {}

Clients::Clients(int idcl, QString nom, QString prenom, QString adresse, QString email, QString telephone, QString status, int anciennete, QDateTime derniereActivite) {
    this->idcl = idcl;
    this->nom = nom;
    this->prenom = prenom;
    this->adresse = adresse;
    this->email = email;
    this->telephone = telephone;
    this->status = status;
    this->anciennete = anciennete;
    this->derniereActivite = derniereActivite;
}

// Method to add a client
bool Clients::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENTS (IDCL, NOM, PRENOM, ADRESSE, EMAIL, TELEPHONE, STATUS, ANCIENNETE, POINTS) "
                  "VALUES (:idcl, :nom, :prenom, :adresse, :email, :telephone, :status, :anciennete, :points)");
    query.bindValue(":idcl", idcl);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":status", status);
    query.bindValue(":anciennete", anciennete);
    query.bindValue(":points", 50);  // Initialise avec 50 points
    query.bindValue(":derniere Activite", QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm"));
    if (!query.exec()) {
        qDebug() << "Erreur dans ajouter :" << query.lastError().text();
        return false;
    }

    return true;
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
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Points"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Dernière Activité"));  // Ajouter la colonne ici

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
}void Clients::verifierInactivite(int idcl)
{
    QSqlQuery query;
    query.prepare("SELECT DERNIERE_ACTIVITE, POINTS, STATUS FROM CLIENTS WHERE IDCL = :idcl");
    query.bindValue(":idcl", idcl);

    if (query.exec() && query.next()) {
        QDateTime derniereActivite = QDateTime::fromString(query.value(0).toString(), "yyyy-MM-dd");
        int points = query.value(1).toInt();
        QString status = query.value(2).toString();

        // Calculer la différence de jours entre la dernière activité et la date actuelle
        int daysDiff = derniereActivite.daysTo(QDateTime::currentDateTime());

        if (status.toLower() == "inactif" && daysDiff > 60) {
            // Réinitialiser les points si inactif depuis plus de 60 jours
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE CLIENTS SET POINTS = 0 WHERE IDCL = :idcl");
            updateQuery.bindValue(":idcl", idcl);

            if (!updateQuery.exec()) {
                qDebug() << "Erreur lors de la réinitialisation des points :" << updateQuery.lastError().text();
            } else {
                qDebug() << "Les points du client ID" << idcl << "ont été réinitialisés à 0 (inactif).";
            }
        } else if (status.toLower() == "actif") {
            // Si le client est actif, ses points restent inchangés
            qDebug() << "Le client ID" << idcl << "est actif et conserve ses points :" << points;
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête pour vérifier l'inactivité :" << query.lastError().text();
    }
}

void Clients::ajouterPoints(int idcl, int points)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENTS SET POINTS = POINTS + :points WHERE IDCL = :idcl");
    query.bindValue(":points", points);
    query.bindValue(":idcl", idcl);

    if (!query.exec()) {
        qDebug() << "Erreur dans ajouterPoints :" << query.lastError().text();
    } else {
        qDebug() << "Points ajoutés avec succès pour le client ID" << idcl;
    }
}

int Clients::calculerPointsFidelite(int idcl)
{
    QSqlQuery query;
    query.prepare("SELECT POINTS FROM CLIENTS WHERE IDCL = :idcl");
    query.bindValue(":idcl", idcl);

    if (query.exec() && query.next()) {
        int points = query.value(0).toInt();  // Récupère la valeur des points depuis la base de données
        return points;
    } else {
        qDebug() << "Erreur dans calculerPointsFidelite :" << query.lastError().text();
    }

    return 0;  // Retourne 0 si aucun résultat ou en cas d'erreur
}
