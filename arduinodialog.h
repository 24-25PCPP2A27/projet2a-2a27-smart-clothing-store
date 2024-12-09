#ifndef ARDUINODIALOG_H
#define ARDUINODIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "arduino.h"

namespace Ui {
class ArduinoDialog;
}

class ArduinoDialog : public QDialog {
    Q_OBJECT

public:
    explicit ArduinoDialog(QWidget *parent = nullptr, Arduino *arduinoInstance = nullptr);
    ~ArduinoDialog();

private slots:
    void readFromArduino(); // Declaration of readFromArduino()
    void searchInDatabase(const QString &id_a); // Declaration of searchInDatabase()
    void connectToArduino();

private:
    Ui::ArduinoDialog *ui;
    Arduino *arduino;
    QString buffer; // To handle multi-character IDs
};

#endif // ARDUINODIALOG_H


/*// ArduinoDialog.h
#ifndef ARDUINODIALOG_H
#define ARDUINODIALOG_H

#include <QDialog>
#include "arduino.h"  // Inclure la classe Arduino

namespace Ui {
class ArduinoDialog;
}

class ArduinoDialog : public QDialog
{
    Q_OBJECT

public:
    // Passer un pointeur à l'instance d'Arduino dans le constructeur
    explicit ArduinoDialog(QWidget *parent = nullptr, Arduino *arduinoInstance = nullptr);
    ~ArduinoDialog();

private:
    Ui::ArduinoDialog *ui;
    Arduino *arduino; // Ajouter un membre pour Arduino
    void connectToArduino();  // Connecter à Arduino
    void readFromArduino();  // Lire depuis Arduino
    QString buffer;
    void searchInDatabase(const QString &id_a);

private slots:
    void on_pushButtonSend_clicked();
    void on_pushButtonDisconnect_clicked();
};

#endif // ARDUINODIALOG_H*/
