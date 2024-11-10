#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "article.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Atmp.AfficherArticles());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    QString IDa=ui->lineEdit_IDa->text();
    QString Type=ui->lineEdit_Type->text();
    int Taille=ui->lineEdit_Taille->text().toInt();
    QString Longueur=ui->lineEdit_Longueur->text();
    QString Couleur=ui->lineEdit_Couleur->text();
    int Quantite=ui->spinBox_Quantite->value();
    float Prix_Unitaire=static_cast<float>(ui->doubleSpinBox_Prix_Unitaire->value());
    QString Marque=ui->lineEdit_Marque->text();
    Article A(IDa,Type,Taille,Longueur,Couleur,Quantite,Prix_Unitaire,Nb_Ar_Vendus,Marque);
    bool test=A.AjouterArticle();
    if (test){
        ui->tableView->setModel(Atmp.AfficherArticles());
        QMessageBox::information(nullptr,QObject::tr("Ok")),
                QObject::tr("Ajout effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_pushButton_supprimer_clicked()
{
    QString IDa=ui->lineEdit_IDa_2->text();
    bool test=Atmp.SupprimerArticle(IDa);
    if (test){
        ui->tableView->setModel(Atmp.AfficherArticles());
        QMessageBox::information(nullptr,QObject::tr("Ok")),
                QObject::tr("Suppression effectuée\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}
