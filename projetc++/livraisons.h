#ifndef LIVRAISON_H
#define LIVRAISON_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

class livraison
{
    int idl;
    QString num_Transporteur;
    QString nom_Transporteur;
    QString adresse_Liv;
    QString statue_Liv;
    float frais_Liv;
    QDate date_Liv;

public:
    // Constructors
    livraison(); // Default constructor
    livraison(int, QString, QString, QString, QString, float, QDate); // Parametrized constructor

    // Getters
    int getIDL() { return idl; }
    QString getNum_Transporteur() { return num_Transporteur; }
    QString getNom_Transporteur() { return nom_Transporteur; }
    QString getAdresse_Liv() { return adresse_Liv; }
    QString getStatue_Liv() { return statue_Liv; }
    float getFrais_Liv() { return frais_Liv; }
    QDate getDate_Liv() { return date_Liv; }

    // Setters
    void setIDL(int id) { idl = id; }
    void setNum_Transporteur(QString num) { num_Transporteur = num; }
    void setNom_Transporteur(QString nom) { nom_Transporteur = nom; }
    void setAdresse_Liv(QString adresse) { adresse_Liv = adresse; }
    void setStatue_Liv(QString statut) { statue_Liv = statut; }
    void setFrais_Liv(float frais) { frais_Liv = frais; }
    void setDate_Liv(QDate date) { date_Liv = date; }

    // Basic functionalities for livraison management
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel *rechercher(QString nom_Transporteur); // Updated to indicate search by `nomTransporteur`
    QSqlQueryModel *tri();
    bool valider(); // Validation function
};

#endif // LIVRAISON_H
