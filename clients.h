#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMap>
#include <QDebug>
#include <QDateTime>

class Clients { // Ensure the class name starts with an uppercase 'C'
public:
    Clients();
    Clients(int idcl, QString nom, QString prenom, QString adresse, QString email, QString telephone, QString status, int anciennete =0 , QDateTime derniereActivite = QDateTime::currentDateTime());

    bool ajouter();
    bool supprimer(int idcl);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercheID(int idcl);
    QSqlQueryModel* trier(bool ordreAscendant);  // Sorting method
    static QMap<QString, int> getStatistiquesByStatus();
    // Points de fidélité
       static int calculerPointsFidelite(int idcl); // Méthode pour calculer les points de fidélité
       void verifierInactivite(int idcl);    // Vérifier si un client est inactif

       // Méthode pour ajouter des points supplémentaires (ex: lors d'une commande)
       static void ajouterPoints(int idcl, int points);

private:
    int idcl;
    QString nom;
    QString prenom;
    QString adresse;
    QString email;
    QString telephone;
    QString status;
    int anciennete;
    QDateTime derniereActivite; // Dernière activité du client

};

#endif
