#ifndef LIVRAISONS_H
#define LIVRAISONS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QDebug>
#include <QSqlError>
#include <QMap>


class livraisons
{
private:
    int IDL;  // Delivery ID
    QString NUM_TRANSPORTEUR;  // Transporter number
    QString NOM_TRANSPORTEUR;  // Transporter's name
    QString ADRESSE_LIV;  // Delivery address
    QString STATUE_LIV;  // Delivery status
    int FRAIS_LIV;  // Delivery fees
    QDate DATE_LIV;  // Delivery date

public:
    // Constructors
    livraisons();  // Default constructor
    livraisons(int id, QString num, QString nom, QString adresse, QString statut, int frais, QDate date);
    QMap<QString, int> getAdresseStats();

    // Getters
    int getIDL();
    QString getNUM_TRANSPORTEUR();
    QString getNOM_TRANSPORTEUR();
    QString getADRESSE_LIV();
    QString getSTATUE_LIV();
    int getFRAIS_LIV();
    QDate getDATE_LIV();

    // Setters
    void setIDL(int id);
    void setNUM_TRANSPORTEUR(QString num);
    void setNOM_TRANSPORTEUR(QString nom);
    void setADRESSE_LIV(QString adresse);
    void setSTATUE_LIV(QString statut);
    void setFRAIS_LIV(int frais);
    void setDATE_LIV(QDate date);

    // Basic functionalities for livraison management
    bool ajouter();
    QSqlQueryModel *display();
    bool supprimer(int id);
    bool modifier(int id);
    QSqlQueryModel *rechercher(int id);
    QSqlQueryModel *tri();
    bool valider();
    bool isDateClose(QDate dateLivraison);
};

#endif // LIVRAISONS_H
