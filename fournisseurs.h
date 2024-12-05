#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "logviewer.h"

class Fournisseurs
{
public:
    // Constructeurs
    Fournisseurs();  // Constructeur par défaut
    Fournisseurs(int IDF, QString NOM, QString PRENOM, QString ADRESSE, QString NUM_TEL, QString CATEGORIE_PROD, int ANCIENNETE, QString EMAIL);  // Constructeur paramétré

    // Méthodes de gestion des fournisseurs
    bool ajouter();  // Méthode pour ajouter un fournisseur
    bool modifier();  // Méthode pour modifier un fournisseur
    bool supprimer(int IDF);  // Méthode pour supprimer un fournisseur

    // Méthodes d'affichage et de recherche
    QSqlQueryModel* afficher();  // Méthode pour afficher les fournisseurs
    //QSqlQueryModel* search(const QString &searchQuery);
     QSqlQueryModel* search(const QString &searchQuery);
   // Méthode de recherche de fournisseur
    QSqlQueryModel* sortByAnciennete();  // Méthode pour trier les fournisseurs par ancienneté

    // Export des données
    bool exportToPDF(const QString &filePath);  // Méthode pour exporter les fournisseurs en PDF

    // Notifications et envoi d'email
    void checkAndSendEmailIfThresholdExceeded();  // Vérifie et envoie un email si le seuil est dépassé
    void notifyStockZero();  // Notifie si le stock est à zéro
    void sendEmail(const QString &recipient, const QString &subject, const QString &body);  // Envoi d'un email

private:
    int IDF;  // ID du fournisseur
    QString NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, EMAIL;  // Informations personnelles
    int ANCIENNETE;  // Ancienneté du fournisseur

    // Méthodes privées pour l'envoi de notifications par email
    void sendEmailNotification(const QString &recipientEmail, const QString &subject, const QString &message);
    QString getSupplierEmailByArticle(int articleID);  // Récupérer l'email du fournisseur à partir de l'ID d'article
};

#endif // FOURNISSEURS_H
