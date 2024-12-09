#ifndef MAINWINDOWARTICLES_H
#define MAINWINDOWARTICLES_H

#include <QMainWindow>
#include <QDialog>
#include <QtSql/QSqlQueryModel>
#include "article.h"
#include <QTableView>
#include <QList>
#include <QStandardItemModel>
#include <QDateTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "arduinooutput.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowArticles; }
QT_END_NAMESPACE

class MainWindowArticles : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowArticles(QWidget *parent = nullptr);
    ~MainWindowArticles();

private slots:
    void on_pushButton_Afficher_clicked();
    void on_pushButton_Modifier_clicked();
    void on_pushButton_Ajouter_clicked();
    void on_pushButton_Exporter_clicked();
    void on_pushButton_Supprimer_clicked();
    void on_stat_clicked();
    void searchArticles(const QString &query);
    void on_pushButton_Trier_clicked();
    void on_pushButton_Image_released();
    void showNextImage();
    void showPreviousImage();
    void refreshCatalog();
    void on_pushButton_CheckStock_clicked();
    void selectFirstLine(QTableView *tableView);
    void on_pushButton_Next_clicked();
    void on_pageFournisseur_clicked();
    void on_pushButton_Vendre_released();
    void on_pageLivraison_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_pageClient_clicked();
    void on_pushButton_Vendre_clicked();

private:
    Ui::MainWindowArticles *ui;
    Article Atmp;
    QTableView *tableView;
    QByteArray selectedImage;
    QVector<QByteArray> imageCatalog; // To store images
    int currentImageIndex;           // Tracks the current image being displayed
    void displayImage(int index);
    ArduinoOutput arduino;
};
#endif // MAINWINDOWARTICLES_H
