#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QString>
#include <QSqlQueryModel>

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




private:
    int IDF;
    QString NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD,EMAIL;
    int ANCIENNETE;

    void checkAndSendEmailIfThresholdExceeded();  // Method to check and send email
    void sendEmailNotification(const QString &message);  // Method to send email notifications

};

#endif // FOURNISSEURS_H
