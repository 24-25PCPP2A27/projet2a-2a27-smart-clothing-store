#include "livraisons.h"

// Default constructor
livraison::livraison()
{
    idl = 0;
    num_Transporteur = "";
    nom_Transporteur = "";
    adresse_Liv = "";
    statue_Liv = "";
    frais_Liv = 0.0f;
    date_Liv = QDate();
}

// Parametrized constructor
livraison::livraison(int idl, QString num_Transporteur, QString nom_Transporteur, QString adresse_Liv,
                     QString statue_Liv, float frais_Liv, QDate date_Liv)
{
    this->idl = idl;
    this->num_Transporteur = num_Transporteur;
    this->nom_Transporteur = nom_Transporteur;
    this->adresse_Liv = adresse_Liv;
    this->statue_Liv = statue_Liv;
    this->frais_Liv = frais_Liv;
    this->date_Liv = date_Liv;
}

// Validation method
bool livraison::valider() {
    // Vérifier que les champs requis ne sont pas vides et que les frais sont valides
    if (num_Transporteur.isEmpty() || nom_Transporteur.isEmpty() || adresse_Liv.isEmpty() ||
        statue_Liv.isEmpty() || frais_Liv < 0 || !date_Liv.isValid()) {
        return false; // Validation échouée
    }
    return true; // Validation réussie
}

// Ajouter method
bool livraison::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO LIVRAISONS (IDL, Num_transporteur, Nom_transporteur, Adresse_liv, Statue_liv, Frais_liv, Date_liv) "
                  "VALUES (:idl, :num_transporteur, :nom_transporteur, :adresse_liv, :statue_liv, CAST(:frais_liv AS NUMBER), :date_liv)");

    query.bindValue(":idl", idl);
    query.bindValue(":num_transporteur", num_Transporteur);
    query.bindValue(":nom_transporteur", nom_Transporteur);
    query.bindValue(":adresse_liv", adresse_Liv);
    query.bindValue(":statue_liv", statue_Liv);
    query.bindValue(":frais_liv", frais_Liv); // Double type should bind directly
    query.bindValue(":date_liv", date_Liv); // QDate binds directly if DB expects a DATE type

    if (query.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return false;
    }
}

// Afficher method
QSqlQueryModel* livraison::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM LIVRAISONS");

    if (model->lastError().isValid())
    {
        qDebug() << "Error in SELECT query:" << model->lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Num_transporteur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom_transporteur"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse_liv"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statue_liv"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Frais_liv"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date_liv"));

    return model;
}

// Supprimer method
bool livraison::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM LIVRAISONS WHERE IDL = :idl");
    query.bindValue(":idl", id);

    return query.exec(); // Returns true if the query executes successfully
}

// Modifier method
bool livraison::modifier(int id)
{
    if (!valider()) {
        qDebug() << "Erreur de validation des données : les données saisies sont invalides.";
        return false; // Validation échouée
    }

    QSqlQuery query;
    query.prepare("UPDATE LIVRAISONS SET NUM_TRANSPORTEUR = :num_Transporteur, NOM_TRANSPORTEUR = :nom_Transporteur, "
                  "ADRESSE_LIV = :adresse_Liv, STATUE_LIV = :statut_Liv, FRAIS_LIV = :frais_Liv, DATE_LIV = :date_Liv "
                  "WHERE IDL = :idl");
    query.bindValue(":idl", id);
    query.bindValue(":num_Transporteur", num_Transporteur);
    query.bindValue(":nom_Transporteur", nom_Transporteur);
    query.bindValue(":adresse_Liv", adresse_Liv);
    query.bindValue(":statut_Liv", statue_Liv);
    query.bindValue(":frais_Liv", frais_Liv);
    query.bindValue(":date_Liv", date_Liv);

    return query.exec();
}

// Rechercher method
QSqlQueryModel* livraison::rechercher(QString nom_Transporteur)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    // Préparer une requête pour rechercher par nom du transporteur
    query.prepare("SELECT * FROM LIVRAISONS WHERE NOM_TRANSPORTEUR LIKE :nom_Transporteur");
    query.bindValue(":nom_Transporteur", "%" + nom_Transporteur + "%");
    query.exec();

    model->setQuery(query);
    return model;
}

// Tri method
QSqlQueryModel* livraison::tri()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM LIVRAISONS ORDER BY DATE_LIV DESC");

    return model;
}
