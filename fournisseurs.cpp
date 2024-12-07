#include "fournisseurs.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include "smtp.h"
#include <QTimer>


Fournisseurs::Fournisseurs()
{
    // Default constructor implementation, if needed.
}

Fournisseurs::Fournisseurs(int IDF, QString NOM, QString PRENOM, QString ADRESSE, QString NUM_TEL, QString CATEGORIE_PROD, int ANCIENNETE, QString EMAIL)
{
    this->IDF = IDF;  // Properly assign IDF
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

    qDebug() << "Adding fournisseur with IDF:" << IDF;  // Debugging line

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
        return false;
    }

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
// Fonction pour supprimer un fournisseur
bool Fournisseurs::supprimer(int IDF){
    QSqlQuery query;

    // Supprimer les enregistrements dépendants dans ARTICLES
    query.prepare("DELETE FROM ARTICLES WHERE IDF = :IDF");
    query.bindValue(":IDF", IDF);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression des enregistrements dépendants:" << query.lastError().text();
        LogViewer::writeLog("Échec de la suppression des enregistrements dépendants pour le fournisseur avec IDF = " + QString::number(IDF) + ". Erreur: " + query.lastError().text());
        return false;
    }

    // Supprimer le fournisseur
    query.prepare("DELETE FROM FOURNISSEURS WHERE IDF = :IDF");
    query.bindValue(":IDF", IDF);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du fournisseur:" << query.lastError().text();
        LogViewer::writeLog("Échec de la suppression du fournisseur avec IDF = " + QString::number(IDF) + ". Erreur: " + query.lastError().text());
        return false;
    }

    LogViewer::writeLog("Suppression réussie du fournisseur avec IDF = " + QString::number(IDF));
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
 QSqlQueryModel* Fournisseurs::search(const QString &searchQuery){
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




/*// Fonction pour supprimer un fournisseur
bool Fournisseurs::supprimer(int IDF){
    QSqlQuery query;

    // Supprimer les enregistrements dépendants dans ARTICLES
    query.prepare("DELETE FROM ARTICLES WHERE IDF = :IDF");
    query.bindValue(":IDF", IDF);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression des enregistrements dépendants:" << query.lastError().text();
        LogViewer::writeLog("Échec de la suppression des enregistrements dépendants pour le fournisseur avec IDF = " + QString::number(IDF) + ". Erreur: " + query.lastError().text());
        return false;
    }

    // Supprimer le fournisseur
    query.prepare("DELETE FROM FOURNISSEURS WHERE IDF = :IDF");
    query.bindValue(":IDF", IDF);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression du fournisseur:" << query.lastError().text();
        LogViewer::writeLog("Échec de la suppression du fournisseur avec IDF = " + QString::number(IDF) + ". Erreur: " + query.lastError().text());
        return false;
    }

    LogViewer::writeLog("Suppression réussie du fournisseur avec IDF = " + QString::number(IDF));
    return true;
}*/







QSqlQueryModel* Fournisseurs::sortByAnciennete()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM FOURNISSEURS ORDER BY ANCIENNETE ASC"); // Tri par ancienneté

    if (!query.exec()) {
        qWarning() << "Error executing query:" << query.lastError().text();
        return nullptr;  // Si la requête échoue, retourner nullptr
    }

    model->setQuery(query);
    return model;
}





/*QSqlQueryModel* Fournisseurs::search(const QString &searchQuery)
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
}*/



bool Fournisseurs::exportToPDF(const QString &filePath) {
    QTextDocument document;
    QString htmlContent;

    // Prepare an HTML table to structure the data
    htmlContent.append("<h1>Fournisseur Report</h1>");
    htmlContent.append("<table border='1' cellspacing='0' cellpadding='5'>");
    htmlContent.append("<tr><th>ID</th><th>Nom</th><th>Prénom</th><th>Adresse</th><th>Numéro de Téléphone</th><th>Catégorie de Produit</th><th>Ancienneté</th><th>Email</th></tr>");

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
        htmlContent.append("<td>" + query.value("EMAIL").toString() + "</td>");
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
}

