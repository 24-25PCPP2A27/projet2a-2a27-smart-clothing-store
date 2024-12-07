#include "livraisons.h"
#include <QtDebug>
#include <QSqlError>

#include <QDateTime>



// Default constructor
livraisons::livraisons() {}

// Parameterized constructor
livraisons::livraisons(int IDL, QString NUM_TRANSPORTEUR, QString NOM_TRANSPORTEUR, QString ADRESSE_LIV,
                     QString STATUE_LIV, int FRAIS_LIV, QDate DATE_LIV) {
    this->IDL = IDL;
    this->NUM_TRANSPORTEUR = NUM_TRANSPORTEUR;
    this->NOM_TRANSPORTEUR = NOM_TRANSPORTEUR;
    this->ADRESSE_LIV = ADRESSE_LIV;
    this->STATUE_LIV = STATUE_LIV;
    this->FRAIS_LIV = FRAIS_LIV;
    this->DATE_LIV = DATE_LIV;
}

// Validation method
bool livraisons::valider() {
    if (NUM_TRANSPORTEUR.isEmpty() || NOM_TRANSPORTEUR.isEmpty() || ADRESSE_LIV.isEmpty() ||
        STATUE_LIV.isEmpty() || FRAIS_LIV < 0 || !DATE_LIV.isValid()) {
        qDebug() << "Validation failed: Invalid data.";
        return false;
    }
    return true;
}

// Ajouter method
bool livraisons::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO LIVRAISONS (IDL, NUM_TRANSPORTEUR, NOM_TRANSPORTEUR, ADRESSE_LIV, STATUE_LIV, FRAIS_LIV, DATE_LIV) "
                  "VALUES (:IDL, :NUM_TRANSPORTEUR, :NOM_TRANSPORTEUR, :ADRESSE_LIV, :STATUE_LIV, :FRAIS_LIV, :DATE_LIV)");
    query.bindValue(":IDL", IDL);
    query.bindValue(":NUM_TRANSPORTEUR", NUM_TRANSPORTEUR);
    query.bindValue(":NOM_TRANSPORTEUR", NOM_TRANSPORTEUR);
    query.bindValue(":ADRESSE_LIV", ADRESSE_LIV);
    query.bindValue(":STATUE_LIV", STATUE_LIV);
    query.bindValue(":FRAIS_LIV", FRAIS_LIV);
    query.bindValue(":DATE_LIV", DATE_LIV);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Add failed:" << query.lastError().text();
        return false;
    }

}

// Afficher method
QSqlQueryModel* livraisons::display() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM LIVRAISONS");  // Adjust query if needed

    if (query.exec()) {
        model->setQuery(query);  // Apply the query to load fresh data
    } else {
        qDebug() << "Select error:" << query.lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM_TRANSPORTEUR"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM_TRANSPORTEUR"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_LIV"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUE_LIV"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("FRAIS_LIV"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_LIV"));

    return model;
}

// Setters Implementation
void livraisons::setIDL(int id) {
    this->IDL = id;
}

void livraisons::setNUM_TRANSPORTEUR(QString num) {
    this->NUM_TRANSPORTEUR = num;
}

void livraisons::setNOM_TRANSPORTEUR(QString nom) {
    this->NOM_TRANSPORTEUR = nom;
}

void livraisons::setADRESSE_LIV(QString adresse) {
    this->ADRESSE_LIV = adresse;
}

void livraisons::setSTATUE_LIV(QString statut) {
    this->STATUE_LIV = statut;
}

void livraisons::setFRAIS_LIV(int frais) {
    this->FRAIS_LIV = frais;
}

void livraisons::setDATE_LIV(QDate date) {
    this->DATE_LIV = date;
}




// Supprimer method
bool livraisons::supprimer(int IDL) {
    QSqlQuery query;
    query.prepare("DELETE FROM LIVRAISONS WHERE IDL = :IDL");  // Delete using the specific IDL
    query.bindValue(":IDL", IDL);

    qDebug() << "Attempting to delete IDL:" << IDL;  // Debug the IDL passed to the query

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            qDebug() << "Record with IDL =" << IDL << "deleted successfully.";
            return true;
        } else {
            qDebug() << "No record found with IDL =" << IDL;
            return false;
        }
    } else {
        qDebug() << "Delete failed:" << query.lastError().text();
        return false;
    }
}




// Modifier method
bool livraisons::modifier(int IDL) {
    if (!valider()) {
        qDebug() << "Validation failed: Cannot modify.";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE LIVRAISONS SET NUM_TRANSPORTEUR = :NUM_TRANSPORTEUR, NOM_TRANSPORTEUR = :NOM_TRANSPORTEUR, "
                  "ADRESSE_LIV = :ADRESSE_LIV, STATUE_LIV = :STATUE_LIV, FRAIS_LIV = :FRAIS_LIV, DATE_LIV = :DATE_LIV "
                  "WHERE IDL = :IDL");
    query.bindValue(":IDL", IDL);
    query.bindValue(":NUM_TRANSPORTEUR", NUM_TRANSPORTEUR);
    query.bindValue(":NOM_TRANSPORTEUR", NOM_TRANSPORTEUR);
    query.bindValue(":ADRESSE_LIV", ADRESSE_LIV);
    query.bindValue(":STATUE_LIV", STATUE_LIV);
    query.bindValue(":FRAIS_LIV", FRAIS_LIV);
    query.bindValue(":DATE_LIV", DATE_LIV);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }
}

// Rechercher method
QSqlQueryModel* livraisons::rechercher(int IDL) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM LIVRAISONS WHERE IDL = :IDL");
    query.bindValue(":IDL", IDL);

    if (!query.exec()) {
        qDebug() << "Search failed:" << query.lastError().text();
    } else {
        model->setQuery(query);
    }

    return model;
}

// Tri method
QSqlQueryModel* livraisons::tri() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM LIVRAISONS ORDER BY DATE_LIV DESC");

    if (model->lastError().isValid()) {
        qDebug() << "Sort failed:" << model->lastError().text();
    }

    return model;
}

//stats:
QMap<QString, int> livraisons::getAdresseStats() {
    QMap<QString, int> stats;
    QSqlQuery query;

    query.prepare("SELECT ADRESSE_LIV, COUNT(*) as count FROM LIVRAISONS GROUP BY ADRESSE_LIV");

    if (!query.exec()) {
        qDebug() << "Error retrieving address statistics:" << query.lastError().text();
    } else {
        while (query.next()) {
            QString adresse = query.value("ADRESSE_LIV").toString();
            int count = query.value("count").toInt();
            stats[adresse] = count;  // Store the address and count in the map
        }
    }

    return stats;
}



bool livraisons::isDateClose(QDate dateLivraison) {
    QDate today = QDate::currentDate();
    int daysDifference = today.daysTo(dateLivraison);


    return daysDifference <= 2 && daysDifference >= 0;
}

