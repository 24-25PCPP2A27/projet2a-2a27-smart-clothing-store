#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QString>
#include <QSqlQueryModel>

class Fournisseurs {
public:
    // Constructors
    Fournisseurs();
    Fournisseurs(int IDF, QString NOM, QString PRENOM, QString ADRESSE, QString NUM_TEL, QString CATEGORIE_PROD, int ANCIENNETE);

    // Methods
    bool ajouter();
    bool modifier();
    bool supprimer(int IDF);
    QSqlQueryModel *afficher();
    void sendEmailNotification(const QString &message);
    void checkAndSendEmailIfThresholdExceeded();

private:
    int IDF;
    QString NOM;
    QString PRENOM;
    QString ADRESSE;
    QString NUM_TEL;
    QString CATEGORIE_PROD;
    int ANCIENNETE;

    // Helper methods
    int calculerANCIENNETETotale();
};

#endif // FOURNISSEURS_H
