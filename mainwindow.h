#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "fournisseurs.h"
#include "emailer.h"
#include <QTableView>
#include<qrcodedialog.h>
#include <QList>
#include <QStandardItemModel>
#include <QDateTime>

struct HistoriqueAction {
    QString action;
    QString details;
    QString date;
};





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


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
    void on_QR_code_clicked();
    void updateHistorique(const QString &action, const QString &details);





private:
    Ui::MainWindow *ui;
    Fournisseurs fournisseur;  // Instance of the Fournisseurs class
    QTableView *tableView;
    QList<HistoriqueAction> historiqueList;
    QStandardItemModel *historiqueModel;

};

#endif // MAINWINDOW_H
