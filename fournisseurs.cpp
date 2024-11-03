#include "fournisseurs.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

Fournisseurs::Fournisseurs()
{
    // Default constructor implementation, if needed.
}

Fournisseurs::Fournisseurs(int IDF, QString NOM, QString PRENOM, QString ADRESSE, QString NUM_TEL, QString CATEGORIE_PROD, int ANCIENNETE)
{
    this->IDF = IDF;
    this->NOM = NOM;
    this->PRENOM = PRENOM;
    this->ADRESSE = ADRESSE;
    this->NUM_TEL = NUM_TEL;
    this->CATEGORIE_PROD = CATEGORIE_PROD;
    this->ANCIENNETE = ANCIENNETE;
}

bool Fournisseurs::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO FOURNISSEURS (IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE) "
                  "VALUES (:IDF, :NOM, :PRENOM, :ADRESSE, :NUM_TEL, :CATEGORIE_PROD, :ANCIENNETE)");

    query.bindValue(":IDF", IDF);
    query.bindValue(":ANCIENNETE", ANCIENNETE);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":NUM_TEL", NUM_TEL);
    query.bindValue(":CATEGORIE_PROD", CATEGORIE_PROD);

    if (!query.exec()) {
        qDebug() << "Add Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Fournisseurs::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEURS SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE, NUM_TEL=:NUM_TEL, "
                  "CATEGORIE_PROD=:CATEGORIE_PROD, ANCIENNETE=:ANCIENNETE WHERE IDF=:IDF");

    query.bindValue(":IDF", IDF);
    query.bindValue(":ANCIENNETE", ANCIENNETE);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":NUM_TEL", NUM_TEL);
    query.bindValue(":CATEGORIE_PROD", CATEGORIE_PROD);

    if (!query.exec()) {
        qDebug() << "Update Error: " << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel *Fournisseurs::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FOURNISSEURS");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numéro de téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Catégorie de produit"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Ancienneté"));

    return model;
}

bool Fournisseurs::supprimer(int IDF)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FOURNISSEURS WHERE IDF=:IDF");
    query.bindValue(":IDF", IDF);

    if (!query.exec()) {
        qDebug() << "Delete Error: " << query.lastError().text();
        return false;
    }
    return true;
}

int Fournisseurs::calculerANCIENNETETotale()
{
    QSqlQuery query;
    int ANCIENNETETotale = 0;

    if (query.exec("SELECT SUM(ANCIENNETE) FROM FOURNISSEURS")) {
        if (query.next()) {
            ANCIENNETETotale = query.value(0).toInt();
        }
    } else {
        qDebug() << "Calculation Error: " << query.lastError().text();
    }

    return ANCIENNETETotale;
}

