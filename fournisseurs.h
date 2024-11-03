#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseurs
{
public:
    Fournisseurs();
    Fournisseurs(int IDF, QString NOM, QString PRENOM, QString ADRESSE, QString NUM_TEL, QString CATEGORIE_PROD, int ANCIENNETE);

    bool ajouter();
    bool modifier();
    QSqlQueryModel* afficher();
    bool supprimer(int idf);
    int calculerANCIENNETETotale();

private:
    int IDF;
    QString NOM;
    QString PRENOM;
    QString ADRESSE;
    QString NUM_TEL;
    QString CATEGORIE_PROD;
    int ANCIENNETE;
};

#endif // FOURNISSEURS_H
