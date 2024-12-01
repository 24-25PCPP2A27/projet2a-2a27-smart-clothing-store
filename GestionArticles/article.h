#ifndef ARTICLE_H
#define ARTICLE_H
#include<QtCore/QString>
#include<QString>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlQueryModel>



class Article
{
public:
    Article();
    Article(int IDA, QString TYPE, QString COULEUR, int QUANTITE, float PRIX_UNITAIRE, int NBR_VENTES, QString MARQUE, QByteArray IMAGE);
    bool AjouterAritcle();
    bool ModifierAritcle();
    bool SupprimerArticle();
    QSqlQueryModel* AfficherArticle();
    QSqlQueryModel* RechercherArticle(const QString &type);
    bool ExporterPDF(const QString &filePath);
    QSqlQueryModel* TrierArticles();
private:
    int IDA, QUANTITE, NBR_VENTES;
    QByteArray IMAGE;
    float PRIX_UNITAIRE;
    QString MARQUE, TYPE, COULEUR;
};

#endif // ARTICLE_H
