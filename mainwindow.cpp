#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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

void MainWindow::on_addButton_clicked()
{
    // Retrieve data from input fields
    int IDF = ui->idInput->text().toInt();
    QString NOM = ui->nomInput->text();
    QString PRENOM = ui->prenomInput->text();
    QString ADRESSE = ui->adresseInput->text();
    QString NUM_TEL = ui->numTelInput->text();
    QString CATEGORIE_PROD = ui->categorieProdInput->text();
    int ANCIENNETE = ui->ancienneteInput->text().toInt();

    Fournisseurs fournisseur(IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE);

    if (fournisseur.ajouter()) {
        QMessageBox::information(this, "Success", "Supplier added successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to add supplier.");
    }
}

void MainWindow::on_modifyButton_clicked()
{
    int IDF = ui->idInput->text().toInt();
    QString NOM = ui->nomInput->text();
    QString PRENOM = ui->prenomInput->text();
    QString ADRESSE = ui->adresseInput->text();
    QString NUM_TEL = ui->numTelInput->text();
    QString CATEGORIE_PROD = ui->categorieProdInput->text();
    int ANCIENNETE = ui->ancienneteInput->text().toInt();

    Fournisseurs fournisseur(IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE);

    if (fournisseur.modifier()) {
        QMessageBox::information(this, "Success", "Supplier modified successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify supplier.");
    }
}

void MainWindow::on_displayButton_clicked()
{
    QSqlQueryModel *model = fournisseur.afficher();
    ui->tableView->setModel(model);
}

void MainWindow::on_deleteButton_clicked()
{
    int IDF = ui->idInput->text().toInt();

    if (fournisseur.supprimer(IDF)) {
        QMessageBox::information(this, "Success", "Supplier deleted successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete supplier.");
    }
}
