#ifndef ARTICLE_H
#define ARTICLE_H
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>


class Article
{
    QString IDa, Type, Longueur, Couleur, Marque;
    int Taille, Quantite, Nb_Ar_Vendus;
    float Prix_Unitaire;
public:
    //CONSTRUCTOR
    Article(){}
    Article(QString,QString,int,QString,QString,int,float,int,QString);
    //getters
    QString getIDa(){return IDa;}
    QString getType(){return Type;}
    int getTaille(){return Taille;}
    QString getLongueur(){return Longueur;}
    QString getCouleur(){return Couleur;}
    int getQuantite(){return Quantite;}
    float getPrix_Unitaire(){return Prix_Unitaire;}
    int getNb_Ar_Vendus(){return Nb_Ar_Vendus;}
    QString getMarque(){return Marque;}
    //setters
    //fonctions
    bool AjouterArticle();
    QSqlQueryModel * AfficherArticles();
    bool SupprimerArticle(QString);
};

#endif // ARTICLE_H
