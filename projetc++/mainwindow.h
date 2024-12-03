#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlRecord>
#include "serialcommunication.h"  // Include the SerialCommunication class

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_afficher_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_recherche_clicked();
    void on_pushButton_sort_clicked();
    void on_pushButton_exportPDF_clicked();
    void on_pushButton_showStats_clicked();
    void sendEmail();
    void onEmailStatus(const QString &status);
    void on_pushButton_modifier_clicked();
    void on_pushButton_sendEmail_clicked();
    void on_pushButton_checkDates_clicked();
    void onArduinoStatusChange();  // Slot to handle status change from Arduino button
    void on_pushButton_calendar_clicked();  // Slot to show the calendar
    void highlightLivraisonDates();         // Highlight dates with livraisons
    void on_calendarWidget_selectionChanged();  // Show livraison details on date selection



private:
    Ui::MainWindow *ui;
    void displayLivraisons();
    SerialCommunication *arduino;  // SerialCommunication object to handle Arduino connection
     int livraisonID = -1;
     QMap<QDate, QList<QSqlRecord>> livraisonDetails;  // Store livraison details by date
};

#endif // MAINWINDOW_H
