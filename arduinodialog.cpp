// ArduinoDialog.cpp
#include "arduinodialog.h"
#include "ui_ArduinoDialog.h"
#include "arduino.h"
#include <QMessageBox>
#include <QTimer>
#include <QSqlQuery>
#include <QSqlError>
ArduinoDialog::ArduinoDialog(QWidget *parent, Arduino *arduinoInstance) :
    QDialog(parent),
    ui(new Ui::ArduinoDialog),
    arduino(arduinoInstance)  // Initialiser le pointeur Arduino
{
    ui->setupUi(this);
    connectToArduino();
    connect(arduino->getserial(), &QSerialPort::readyRead, this, &ArduinoDialog::readFromArduino);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ArduinoDialog::readFromArduino);
    timer->start(50); // Check every 50 ms

}

ArduinoDialog::~ArduinoDialog()
{
    delete ui;
}

void ArduinoDialog::connectToArduino()
{
    int result = arduino->connect_arduino();
    if (result == 0) {
        qDebug() << "Arduino connecté!";
        // Connexion du signal readyRead au slot readFromArduino
        connect(arduino->getserial(), &QSerialPort::readyRead, this, &ArduinoDialog::readFromArduino);
    } else if (result == 1) {
        QMessageBox::critical(this, "Erreur", "Échec de l'ouverture du port série!");
    } else {
        QMessageBox::critical(this, "Erreur", "Arduino non trouvé!");
    }
}

/*void ArduinoDialog::readFromArduino()
{
    // Lire les données provenant de l'Arduino
    QByteArray data = arduino->read_from_arduino();

    if (!data.isEmpty()) {
        // Convertir les données reçues en QString
        QString receivedData = QString::fromUtf8(data.trimmed());

        // Déboguer pour vérifier les données reçues
        qDebug() << "Données reçues depuis Arduino : " << receivedData;

        // Mettre à jour le QLineEdit nommé lineEditData avec les données reçues
        ui->lineEdit->setText(receivedData);
    }
}*/
void ArduinoDialog::readFromArduino() {
    QByteArray data = arduino->read_from_arduino(); // Read from Arduino
    if (!data.isEmpty()) {
        QString receivedText = QString::fromUtf8(data); // Convert to QString
        for (QChar c : receivedText) { // Iterate through received characters
            if (c == '#') {
                ui->lineEdit->setText(buffer.trimmed()); // Update the lineEdit
                searchInDatabase(buffer.trimmed());      // Search in the database
                buffer.clear();                         // Clear the buffer
            } else if (c == '*') {
                // Handle deletion when * is pressed
                QString currentText = ui->lineEdit->text();
                if (!currentText.isEmpty()) {
                    currentText.chop(1); // Remove the last character
                    ui->lineEdit->setText(currentText); // Update the lineEdit
                    buffer.chop(1);      // Remove the last character from the buffer
                }
            } else if (!c.isSpace()) {
                // Accumulate data in the buffer
                buffer.append(c);
            }
        }
    }
}


void ArduinoDialog::searchInDatabase(const QString &id_a) {
    QSqlQuery query;
    query.prepare("SELECT IDA, QUANTITE FROM ARTICLES WHERE IDA = :id_a");
    query.bindValue(":id_a", id_a);

    if (query.exec()) {
        if (query.next()) { // If a record is found
            QString id = query.value("IDA").toString();
            QString quantity = query.value("QUANTITE").toString();

            // Display results (update UI widgets as needed)
            ui->label->setText("IDA: " + id + ", QUANTITE: " + quantity);
        } else {
            ui->label->setText("No matching record found.");
        }
    } else {
        qDebug() << "Database query error: " << query.lastError().text();
    }
}




void ArduinoDialog::on_pushButtonSend_clicked()
{
    QByteArray dataToSend = ui->lineEdit->text().toUtf8();
    arduino->write_to_arduino(dataToSend);
    qDebug() << "Données envoyées à Arduino : " << dataToSend;
}

void ArduinoDialog::on_pushButtonDisconnect_clicked()
{
    if (arduino->close_arduino() == 0) {
        qDebug() << "Arduino déconnecté!";
    } else {
        qDebug() << "Échec de la déconnexion!";
    }
}
