#ifndef CLIENTS_H
#define CLIENTS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMap>
#include <QDebug>

class Clients { // Ensure the class name starts with an uppercase 'C'
public:
    Clients();
    Clients(int idcl, QString nom, QString prenom, QString adresse, QString email, QString telephone, QString status, int anciennete);

    bool ajouter();
    bool supprimer(int idcl);
    bool modifier();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercheID(int idcl);
    QSqlQueryModel* trier(bool ordreAscendant);  // Sorting method
    static QMap<QString, int> getStatistiquesByStatus();
    int calculerPointsFidelite(int idcl);

private:
    int idcl;
    QString nom;
    QString prenom;
    QString adresse;
    QString email;
    QString telephone;
    QString status;
    int anciennete;
};

#endif
