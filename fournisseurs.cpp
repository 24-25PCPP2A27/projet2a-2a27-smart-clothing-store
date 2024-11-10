#include "fournisseurs.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include "emailer.h"  // Include the emailer header

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

    // Check if the total seniority exceeds a threshold and send an email
    checkAndSendEmailIfThresholdExceeded();

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

    // Check if the total seniority exceeds a threshold and send an email
    checkAndSendEmailIfThresholdExceeded();

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

void Fournisseurs::checkAndSendEmailIfThresholdExceeded()
{
    // Check if the quantity of any article in the ARTICLES table is 0
    QSqlQuery query;
    query.prepare("SELECT * FROM ARTICLES WHERE QUANTITE = 0");
    if (query.exec()) {
        if (query.next()) {
            // If quantity reaches zero, send an email notification
            sendEmailNotification("One of the articles has reached zero quantity.");
        }
    } else {
        qDebug() << "Error checking article quantity: " << query.lastError().text();
    }
}

void Fournisseurs::sendEmailNotification(const QString &message)
{
    // Email account credentials (replace with actual values)
    QString email = "jemai.ilef@esprit.tn";   // Sender's email address
    QString password = "Blanca1Rico23";        // Sender's email password (use environment variable for better security)
    QString host = "smtp.outlook.com";          // SMTP server (use Gmail's SMTP server if using Gmail)
    int port = 587;                            // Port (587 for TLS)
    int timeout = 10000;                       // Timeout in milliseconds

    // Create emailer instance and send email
    emailer *emailerObj = new emailer(email, password, host, port, timeout);

    // Send email notification using emailerObj
    emailerObj->sendEmailNotification(message);

    // Clean up after sending the email
    delete emailerObj;
}
