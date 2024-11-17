#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots: // Ensure that these methods are declared as slots
    void on_pushButton_ajouter_clicked();
    void on_pushButton_afficher_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_recherche_clicked();
    void on_pushButton_sort_clicked();
    void on_pushButton_exportPDF_clicked();
    void on_pushButton_showStats_clicked();


private:
    Ui::MainWindow *ui;
    void displayLivraisons();


};
#endif // MAINWINDOW_H
