#ifndef MAINFOURNISSEUR_H
#define MAINFOURNISSEUR_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "fournisseurs.h"
#include <QTableView>
#include <QList>
#include <QStandardItemModel>
#include <QDateTime>
#include "arduino.h"
#include "mail.h"

namespace Ui {
class mainFournisseur;
}

class mainFournisseur : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainFournisseur(QWidget *parent = nullptr);  // Constructor
    ~mainFournisseur();  // Destructor

private slots:
    void on_addButton_clicked();  // Slot for add button
    void on_modifyButton_clicked();  // Slot for modify button
    void on_displayButton_clicked();  // Slot for display button
    void on_supprimer_Button_2_clicked();  // Slot for delete button
    void handleEmailStatus(const QString &status);  // Slot to handle email status
    void searchFournisseurs(const QString &query);  // Slot to search suppliers
    void initializeCategoryComboBox();  // Slot to initialize combo box for categories
    void onStatButtonClicked();  // Slot for statistics button
    void exportDataToPDF();  // Slot to export data to PDF
    void on_tri_clicked();  // Slot for sorting suppliers
    void on_openLogViewerButton_clicked();  // Slot for opening log viewer
    void on_openArduinoDialogButton_clicked();  // Slot for opening Arduino dialog
    void on_openMailButton_clicked();  // Slot for opening mail widget
    void on_pageClient_clicked();
    void on_pageLivraison_clicked();

private:
    Ui::mainFournisseur *ui;  // UI object
    Fournisseurs fournisseur;  // Instance of the Fournisseurs class
    QTableView *tableView;  // Table view for displaying suppliers
    Arduino arduino;  // Instance of Arduino class for handling hardware interactions
    mail *mailWidget;  // Pointer to mail widget for email functionalities

};

#endif // MAINFOURNISSEUR_H
