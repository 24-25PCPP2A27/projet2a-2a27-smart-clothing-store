#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QString>
#include <QSqlQueryModel>
#include "logviewer.h"
#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>



class Fournisseurs
{
public:

    Fournisseurs();  // Default constructor
    Fournisseurs(int IDF, QString NOM, QString PRENOM, QString ADRESSE, QString NUM_TEL, QString CATEGORIE_PROD, int ANCIENNETE, QString EMAIL);  // Parameterized constructor

    bool ajouter();  // Method to add supplier
    bool modifier();  // Method to modify supplier
    bool supprimer(int IDF);  // Method to delete supplier
    QSqlQueryModel* afficher();  // Method to display suppliers
    QSqlQueryModel* search(const QString &searchQuery);
    bool exportToPDF(const QString &filePath);
    QSqlQueryModel* sortByAnciennete();
    void checkAndSendEmailIfThresholdExceeded();
    void notifyStockZero();
    void sendEmail(const QString &recipient, const QString &subject, const QString &body);






private:
    int IDF;
    QString NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD,EMAIL;
    int ANCIENNETE;




    void sendEmailNotification(const QString &recipientEmail, const QString &subject, const QString &message);
    QString getSupplierEmailByArticle(int articleID);



};

#endif // FOURNISSEURS_H
