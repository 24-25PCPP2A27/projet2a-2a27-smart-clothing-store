#include "fournisseurs.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include "emailer.h"  // Include the emailer header
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>


Fournisseurs::Fournisseurs()
{
    // Default constructor implementation, if needed.
}

Fournisseurs::Fournisseurs(int IDF, QString NOM, QString PRENOM, QString ADRESSE, QString NUM_TEL, QString CATEGORIE_PROD, int ANCIENNETE,QString EMAIL)
{
    this->IDF = IDF;
    this->NOM = NOM;
    this->PRENOM = PRENOM;
    this->ADRESSE = ADRESSE;
    this->NUM_TEL = NUM_TEL;
    this->CATEGORIE_PROD = CATEGORIE_PROD;
    this->ANCIENNETE = ANCIENNETE;
    this->EMAIL = EMAIL;
}

bool Fournisseurs::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO FOURNISSEURS (IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE , EMAIL) "
                  "VALUES (:IDF, :NOM, :PRENOM, :ADRESSE, :NUM_TEL, :CATEGORIE_PROD, :ANCIENNETE,:EMAIL)");

    query.bindValue(":IDF", IDF);
    query.bindValue(":ANCIENNETE", ANCIENNETE);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":NUM_TEL", NUM_TEL);
    query.bindValue(":CATEGORIE_PROD", CATEGORIE_PROD);
    query.bindValue(":EMAIL", EMAIL);

    if (!query.exec()) {
        qDebug() << "Add Error: " << query.lastError().text();
        LogViewer::writeLog("Failed to add fournisseur with IDF = " + QString::number(IDF) + ". Error: " + query.lastError().text());
        return false;
    }

    LogViewer::writeLog("Successfully added fournisseur with IDF = " + QString::number(IDF));
    checkAndSendEmailIfThresholdExceeded();
    return true;
}


bool Fournisseurs::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEURS SET NOM = :NOM, PRENOM = :PRENOM, ADRESSE = :ADRESSE, NUM_TEL = :NUM_TEL, "
                  "CATEGORIE_PROD = :CATEGORIE_PROD, ANCIENNETE = :ANCIENNETE WHERE IDF = :IDF");

    query.bindValue(":IDF", IDF);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":NUM_TEL", NUM_TEL);
    query.bindValue(":CATEGORIE_PROD", CATEGORIE_PROD);
    query.bindValue(":ANCIENNETE", ANCIENNETE);

    if (!query.exec()) {
        qDebug() << "Update Error: " << query.lastError().text();
        LogViewer::writeLog("Failed to update fournisseur with IDF = " + QString::number(IDF) + ". Error: " + query.lastError().text());
        return false;
    }

    LogViewer::writeLog("Successfully updated fournisseur with IDF = " + QString::number(IDF));
    return true;
}


QSqlQueryModel* Fournisseurs::afficher()
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

    // Delete dependent records in ARTICLES
    query.prepare("DELETE FROM ARTICLES WHERE IDF = :IDF");
    query.bindValue(":IDF", IDF);
    if (!query.exec()) {
        qDebug() << "Error deleting dependent records:" << query.lastError().text();
        LogViewer::writeLog("Failed to delete dependent records for fournisseur with IDF = " + QString::number(IDF) + ". Error: " + query.lastError().text());
        return false;
    }

    // Delete the supplier
    query.prepare("DELETE FROM FOURNISSEURS WHERE IDF = :IDF");
    query.bindValue(":IDF", IDF);
    if (!query.exec()) {
        qDebug() << "Error deleting supplier:" << query.lastError().text();
        LogViewer::writeLog("Failed to delete fournisseur with IDF = " + QString::number(IDF) + ". Error: " + query.lastError().text());
        return false;
    }

    LogViewer::writeLog("Successfully deleted fournisseur with IDF = " + QString::number(IDF));
    return true;
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


QSqlQueryModel* Fournisseurs::sortByAnciennete() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM Fournisseurs ORDER BY ANCIENNETE ASC"); // Tri par ancienneté

    if (!query.exec()) {
        qWarning() << "Error executing query:" << query.lastError().text();
        return nullptr;  // Si la requête échoue, retourner nullptr
    }

    model->setQuery(query);
    return model;
}





QSqlQueryModel* Fournisseurs::search(const QString &searchQuery)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // SQL query to search across NOM, PRENOM, and CATEGORIE_PROD fields
    QString queryStr = "SELECT * FROM FOURNISSEURS WHERE "
                       "NOM LIKE :query OR "
                       "PRENOM LIKE :query OR "
                       "CATEGORIE_PROD LIKE :query";

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":query", "%" + searchQuery + "%"); // Use wildcards for partial matching

    if (query.exec()) {
        model->setQuery(query);

        // Optionally set column headers for your table
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numéro de téléphone"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Catégorie de produit"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Ancienneté"));
    } else {
        qDebug() << "Error in query execution: " << query.lastError();
    }

    return model;
}



bool Fournisseurs::exportToPDF(const QString &filePath) {
    QTextDocument document;
    QString htmlContent;

    // Prepare an HTML table to structure the data
    htmlContent.append("<h1>Fournisseur Report</h1>");
    htmlContent.append("<table border='1' cellspacing='0' cellpadding='5'>");
    htmlContent.append("<tr><th>ID</th><th>Nom</th><th>Prenom</th><th>Adresse</th><th>Numéro de Téléphone</th><th>Catégorie Produit</th><th>Ancienneté</th></tr>");

    // Query the database to get Fournisseurs data
    QSqlQuery query("SELECT * FROM FOURNISSEURS");
    while (query.next()) {
        htmlContent.append("<tr>");
        htmlContent.append("<td>" + query.value("IDF").toString() + "</td>");
        htmlContent.append("<td>" + query.value("NOM").toString() + "</td>");
        htmlContent.append("<td>" + query.value("PRENOM").toString() + "</td>");
        htmlContent.append("<td>" + query.value("ADRESSE").toString() + "</td>");
        htmlContent.append("<td>" + query.value("NUM_TEL").toString() + "</td>");
        htmlContent.append("<td>" + query.value("CATEGORIE_PROD").toString() + "</td>");
        htmlContent.append("<td>" + query.value("ANCIENNETE").toString() + "</td>");
        htmlContent.append("</tr>");
    }
    htmlContent.append("</table>");

    // Set the HTML content to the document
    document.setHtml(htmlContent);

    // Set up the printer for PDF output
    QPrinter printer((QPrinter::PrinterResolution));
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Print the document to the specified PDF file
    document.print(&printer);

    return true;  // Return true to indicate success
};
