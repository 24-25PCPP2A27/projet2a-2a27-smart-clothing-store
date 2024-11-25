#ifndef GESTCLIENTS_H
#define GESTCLIENTS_H

#include <QWidget>
#include <QMainWindow>
#include "clients.h"
#include <QSqlQueryModel>
#include <QMap>

#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class GestClients; }
QT_END_NAMESPACE

class GestClients : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestClients(QWidget *parent = nullptr);
    ~GestClients();
    void afficherStatistiques();



private slots:
    // Slots pour les boutons CRUD
    void on_ajouter_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_trier_clicked();
    void on_rechercheID_clicked();
    void on_pdf_clicked(); // Fonction pour exporter en PDF
    void on_stats_clicked();
    void on_fid_clicked(); // Méthode pour gérer le clic sur le bouton de fidélité


private:
    Ui::GestClients *ui;
    Clients Ctmp;
     bool ordreAscendant = true;
     QSqlQueryModel *modelClients; // Le modèle contenant les données des clients
     Clients* clients; // Instance de la classe Clients


};




#endif
