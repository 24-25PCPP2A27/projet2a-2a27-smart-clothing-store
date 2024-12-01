#include "article.h"
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>

Article::Article()
{

}

Article::Article(int IDA, QString TYPE, QString COULEUR, int QUANTITE, float PRIX_UNITAIRE, int NBR_VENTES, QString MARQUE, QByteArray IMAGE)
{
    this->IDA=IDA;
    this->TYPE=TYPE;
    this->COULEUR=COULEUR;
    this->QUANTITE=QUANTITE;
    this->PRIX_UNITAIRE=PRIX_UNITAIRE;
    this->NBR_VENTES=NBR_VENTES;
    this->MARQUE=MARQUE;
    this->IMAGE=IMAGE;
}

bool Article::AjouterAritcle()
{
    QSqlQuery query;
    QString ida = QString::number(IDA);
    QString quantite = QString::number(QUANTITE);
    QString prixu = QString::number(PRIX_UNITAIRE);
    query.prepare("INSERT INTO ARTICLES (IDA, TYPE, COULEUR, QUANTITE, PRIX_UNITAIRE, NBR_VENTES, MARQUE, IMAGE) "
                  "VALUES (:IDA, :TYPE, :COULEUR, :QUANTITE, :PRIX_UNITAIRE, :NBR_VENTES, :MARQUE, :IMAGE)");

    query.bindValue(":IDA", ida);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":COULEUR", COULEUR);
    query.bindValue(":QUANTITE", quantite);
    query.bindValue(":PRIX_UNITAIRE", prixu);
    query.bindValue(":NBR_VENTES", "0");
    query.bindValue(":MARQUE", MARQUE);
    query.bindValue(":IMAGE", IMAGE);

    if (!query.exec()) {
        qDebug() << "Add Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Article::ModifierAritcle()
{
    QSqlQuery query;
    QString ida = QString::number(IDA);
    QString quantite = QString::number(QUANTITE);
    QString prixu = QString::number(PRIX_UNITAIRE);
    query.prepare("UPDATE ARTICLES SET TYPE = :TYPE, COULEUR = :COULEUR, QUANTITE = :QUANTITE, "
                  "PRIX_UNITAIRE = :PRIX_UNITAIRE, MARQUE = :MARQUE, IMAGE = :IMAGE WHERE IDA = :IDA");

    query.bindValue(":IDA", ida);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":COULEUR", COULEUR);
    query.bindValue(":QUANTITE", quantite);
    query.bindValue(":PRIX_UNITAIRE", prixu);
    query.bindValue(":MARQUE", MARQUE);
    query.bindValue(":IMAGE", IMAGE);

    if (!query.exec()) {
        qDebug() << "Update Error: " << query.lastError().text();
        return false;
    }

    qDebug() << "Article updated successfully.";
    return true;
}

bool Article::SupprimerArticle()
{
    QSqlQuery query;
    query.prepare("DELETE FROM ARTICLES WHERE IDA = :IDA");
    query.bindValue(":IDA", IDA);

    if (!query.exec()) {
        qDebug() << "Delete Error: " << query.lastError().text();
        return false;
    }

    qDebug() << "Article deleted successfully.";
    return true;
}

QSqlQueryModel* Article::AfficherArticle()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM ARTICLES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Couleur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix Unitaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nombre de Ventes"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Marque"));

    return model;
}

QSqlQueryModel* Article::RechercherArticle(const QString &type)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM ARTICLES WHERE TYPE = :TYPE");
    query.bindValue(":TYPE", type);

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Search Error: " << query.lastError().text();
    }

    return model;
}

QSqlQueryModel* Article::TrierArticles()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM ARTICLES ORDER BY PRIX_UNITAIRE ASC");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Sort Error: " << query.lastError().text();
        return nullptr;
    }

    return model;
}

bool Article::ExporterPDF(const QString &filePath)
{
    QTextDocument document;
    QString htmlContent;

    htmlContent.append("<h1>Article Report (Out of Stock)</h1>");
    htmlContent.append("<table border='1' cellspacing='0' cellpadding='5'>");
    htmlContent.append("<tr><th>ID</th><th>Type</th><th>Longueur</th><th>Couleur</th><th>Quantité</th><th>Prix Unitaire</th><th>Marque</th></tr>");

    QSqlQuery query("SELECT * FROM ARTICLES WHERE QUANTITE = 0");
    while (query.next()) {
        htmlContent.append("<tr>");
        htmlContent.append("<td>" + query.value("IDA").toString() + "</td>");
        htmlContent.append("<td>" + query.value("TYPE").toString() + "</td>");
        htmlContent.append("<td>" + query.value("COULEUR").toString() + "</td>");
        htmlContent.append("<td>" + query.value("QUANTITE").toString() + "</td>");
        htmlContent.append("<td>" + query.value("PRIX_UNITAIRE").toString() + "</td>");
        htmlContent.append("<td>" + query.value("MARQUE").toString() + "</td>");
        htmlContent.append("</tr>");
    }
    htmlContent.append("</table>");

    document.setHtml(htmlContent);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    document.print(&printer);

    return true;
}
