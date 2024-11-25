#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "fournisseurs.h"
#include "emailer.h"
#include <QTableView>
#include <QList>
#include <QStandardItemModel>
#include <QDateTime>
#include "arduino.h"







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
    void on_openLogViewerButton_clicked();
    void on_openArduinoDialogButton_clicked();








private:
    Ui::MainWindow *ui;
    Fournisseurs fournisseur;  // Instance of the Fournisseurs class
    QTableView *tableView;
    Arduino arduino;


};

#endif // MAINWINDOW_H
