#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "livraisons.h"
#include <QMessageBox>
#include <QDebug>

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    // Récupérer les données des champs de saisie
    int idl = ui->lineEdit_ID->text().toInt();  // IDL should be an integer
    QString num_Transporteur = ui->lineEdit_NumTransporteur->text().trimmed();  // Trim any extra spaces
    QString nom_Transporteur = ui->lineEdit_NomTransporteur->text().trimmed();  // Trim any extra spaces
    QString adresse_Liv = ui->lineEdit_AdresseLiv->text().trimmed();  // Trim any extra spaces
    QString statue_Liv = ui->lineEdit_StatutLiv->text().trimmed();  // Trim any extra spaces
    float frais_Liv = ui->lineEdit_FraisLiv->text().toFloat();  // Convert text to float for frais_Liv
    QDate date_Liv = ui->dateEdit_DateLiv->date();  // Retrieve the date from the date editor

    // Créer l'objet livraison avec les données sans validation
    livraison l(idl, num_Transporteur, nom_Transporteur, adresse_Liv, statue_Liv, frais_Liv, date_Liv);

    // Appeler la fonction ajouter et gérer le résultat
    if (l.ajouter()) {
        QMessageBox::information(this, "Succès", "Livraison ajoutée avec succès.");
        on_pushButton_afficher_clicked(); // Mettre à jour la table
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de la livraison.");
    }
}

void MainWindow::on_pushButton_afficher_clicked()
{
    livraison L;
    QSqlQueryModel *model = L.afficher();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    QStringList headers = {"ID", "Num_transporteur", "Nom_transporteur", "Adresse_liv", "Statue_liv", "Frais_liv", "Date_liv"};
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    qDebug() << "Displaying data in tableWidget:";

    for (int row = 0; row < model->rowCount(); ++row) {
        ui->tableWidget->insertRow(row);

        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            QTableWidgetItem *item = new QTableWidgetItem(data);
            ui->tableWidget->setItem(row, col, item);

            qDebug() << "Row" << row << "Col" << col << ":" << data;
        }
    }

    ui->tableWidget->repaint();
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int idl = ui->lineEdit_ID->text().toInt();

    if (idl == 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid ID to delete.");
        return;
    }

    livraison L;
    bool success = L.supprimer(idl);

    if (success) {
        QMessageBox::information(this, "Success", "Delivery was successfully deleted.");
        on_pushButton_afficher_clicked();  // Refresh table display
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete the delivery.");
    }
}
