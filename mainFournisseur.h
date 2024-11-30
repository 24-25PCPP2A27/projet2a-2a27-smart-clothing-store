#ifndef mainFournisseur_H
#define mainFournisseur_H

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
    explicit mainFournisseur(QWidget *parent = nullptr);
    ~mainFournisseur();


private slots:
    void on_addButton_clicked();
    void on_modifyButton_clicked();
    void on_displayButton_clicked();
    void on_supprimer_Button_2_clicked();
    void handleEmailStatus(const QString &status);  // Slot to handle email statu
    void searchFournisseurs(const QString &query);
    void initializeCategoryComboBox();
    void onStatButtonClicked();
    void exportDataToPDF();
    void on_tri_clicked();
    void on_openLogViewerButton_clicked();
    void on_openArduinoDialogButton_clicked();
    void on_openMailButton_clicked();










private:
    Ui::mainFournisseur *ui;
    Fournisseurs fournisseur;  // Instance of the Fournisseurs class
    QTableView *tableView;
    Arduino arduino;
    mail *mailWidget;


};

#endif // mainFournisseur_H
