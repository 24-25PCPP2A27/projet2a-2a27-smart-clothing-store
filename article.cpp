#include "article.h"

Article::Article(QString IDa,QString Type,int Taille,QString Longueur,QString Couleur,int Quantite,float Prix_Unitaire,int Nb_Ar_Vendus,QString Marque)
{
    this->IDa=IDa;
    this->Type=Type;
    this->Taille=Taille;
    this->Longueur=Longueur;
    this->Couleur=Couleur;
    this->Quantite=Quantite;
    this->Prix_Unitaire=Prix_Unitaire;
    this->Nb_Ar_Vendus=Nb_Ar_Vendus;
    this->Marque=Marque;
}

bool Article::AjouterArticle()
{
    QSqlQuery query;
    QString t=QString::number(Taille);
    QString q=QString::number(Quantite);
    QString nav="0";
    QString pu=QString::number(Prix_Unitaire);
    query.prepare("insert into article (id, type, taille, longueur, couleur, quantite, prix_unitaire, nbr_articles_vendus, marque)" "values (:id, :type, :taille, :longueur, :couleur, :quantite, :prix_unitaire, :nbr_articles_vendus, :marque)");
    query.bindValue(":id",IDa);
    query.bindValue(":type",Type);
    query.bindValue(":taille",t);
    query.bindValue(":longueur",Longueur);
    query.bindValue(":couleur",Couleur);
    query.bindValue(":quantite",q);
    query.bindValue(":prix_unitaire",pu);
    query.bindValue(":nbr_articles_vendus",nav);
    query.bindValue(":marque",Marque);
    return query.exec();
}

QSqlQueryModel * Article::AfficherArticles()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Article");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Taille"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Longueur"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Couleur"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Quantité"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Prix Unitaire"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Nombre des ventes"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Marque"));
    return model;
}

bool Article::SupprimerArticle(QString ida)
{
    QSqlQuery query;
    query.prepare("Delete from Article where ID= :id");
    query.bindValue(":id",ida);
    return query.exec();
}
