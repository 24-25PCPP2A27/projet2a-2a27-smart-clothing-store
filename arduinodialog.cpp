// ArduinoDialog.cpp
#include "arduinodialog.h"
#include "ui_ArduinoDialog.h"
#include "arduino.h"
#include <QMessageBox>
#include <QTimer>

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
    QByteArray data = arduino->read_from_arduino(); // Call the existing function
    if (!data.isEmpty()) {
        QString receivedText = QString::fromUtf8(data); // Convert to QString
        for (QChar c : receivedText) { // Iterate through each character
            if (c == '#') {
                // End of input detected, display the buffer
                ui->lineEdit->setText(buffer); // Display the full sequence
                buffer.clear(); // Clear the buffer for the next input
            } else {
                // Accumulate data in the buffer
                buffer.append(c);
            }
        }
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
