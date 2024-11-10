#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "fournisseurs.h"
#include "emailer.h"

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
    void on_deleteButton_clicked();
    void handleEmailStatus(const QString &status);  // Slot to handle email status

private:
    Ui::MainWindow *ui;
    Fournisseurs fournisseur;  // Instance of the Fournisseurs class
};

#endif // MAINWINDOW_H
