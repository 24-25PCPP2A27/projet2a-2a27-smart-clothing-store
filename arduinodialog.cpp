#include "arduinodialog.h"
#include "ui_arduinodialog.h"
#include <QMessageBox>

// Constructor and destructor
ArduinoDialog::ArduinoDialog(QWidget *parent, Arduino *arduinoInstance)
    : QDialog(parent), ui(new Ui::ArduinoDialog), arduino(arduinoInstance) {
    ui->setupUi(this);
    connectToArduino(); // Connect Arduino on initialization
    connect(arduino->getserial(), &QSerialPort::readyRead, this, &ArduinoDialog::readFromArduino);
}

ArduinoDialog::~ArduinoDialog() {
    delete ui;
}

void ArduinoDialog::connectToArduino() {
    int result = arduino->connect_arduino();
    if (result == 0) {
        qDebug() << "Arduino connected successfully!";
        // Ensure readyRead signal is connected to the readFromArduino slot
        connect(arduino->getserial(), &QSerialPort::readyRead, this, &ArduinoDialog::readFromArduino);
    } else if (result == 1) {
        qDebug() << "Failed to open the serial port!";
        QMessageBox::critical(this, "Error", "Failed to open the serial port!");
    } else {
        qDebug() << "Arduino not found!";
        QMessageBox::critical(this, "Error", "Arduino not found!");
    }
}


// Implementation of readFromArduino
void ArduinoDialog::readFromArduino() {
    QByteArray data = arduino->read_from_arduino();
    if (!data.isEmpty()) {
        QString id = QString::fromUtf8(data).trimmed();
        qDebug() << "Received ID: " << id;

        // Search the database
        searchInDatabase(id);
    }
}

// Implementation of searchInDatabase
void ArduinoDialog::searchInDatabase(const QString &id_a) {
    QSqlQuery query;
    query.prepare("SELECT IDA, QUANTITE FROM ARTICLES WHERE IDA = :id_a");
    query.bindValue(":id_a", id_a);

    if (query.exec()) {
        QString message;
        if (query.next()) {
            QString quantity = query.value("QUANTITE").toString();
            message = "ID: " + id_a + " Qty: " + quantity;
        } else {
            message = "ID Not Found!";
        }

        // Send the result back to Arduino
        arduino->write_to_arduino(message.toUtf8());
        qDebug() << "Sent to Arduino: " << message;
    } else {
        qDebug() << "Database query error: " << query.lastError().text();
        arduino->write_to_arduino("Error querying DB");
    }
}



/*#include "arduinodialog.h"
#include "ui_arduinodialog.h"
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
}*/





/*void ArduinoDialog::readFromArduino() {
    QByteArray data = arduino->read_from_arduino();
    if (!data.isEmpty()) {
        QString receivedText = QString::fromUtf8(data);  // Convertit les données en texte
        for (const QChar &c : receivedText) {
            if (c == '#') {
                // Si on rencontre le caractère '#', on récupère l'ID du buffer
                QString id = buffer.trimmed();  // Enlève les espaces superflus
                ui->lineEdit->setText(id);  // Affiche l'ID dans le QLineEdit
                searchInDatabase(id);  // Recherche l'ID dans la base de données
                buffer.clear();  // Réinitialise le buffer pour le prochain ID
            } else if (c == '*') {
                // Si on rencontre '*', on enlève le dernier caractère du buffer
                if (!buffer.isEmpty()) {
                    buffer.chop(1);
                    ui->lineEdit->setText(buffer);  // Met à jour le QLineEdit avec le contenu du buffer
                }
            } else if (!c.isSpace()) {
                // Si le caractère n'est pas un espace, on l'ajoute au buffer
                buffer.append(c);
                ui->lineEdit->setText(buffer);  // Met à jour le QLineEdit avec le buffer actuel
            }
        }
    }
}*/

/*void ArduinoDialog::readFromArduino() {
    QByteArray data = arduino->read_from_arduino();
    if (!data.isEmpty()) {
        QString receivedText = QString::fromUtf8(data);  // Convertit les données en texte
        for (const QChar &c : receivedText) {
            if (c == '#') {
                // Si on rencontre le caractère '#', on récupère l'ID du buffer
                QString id = buffer.trimmed();  // Enlève les espaces superflus
                ui->lineEdit->setText(id);  // Affiche l'ID dans le QLineEdit
                searchInDatabase(id);  // Recherche l'ID dans la base de données
                buffer.clear();  // Réinitialise le buffer pour le prochain ID
            } else if (c == '*') {
                // Si on rencontre '*', on enlève le dernier caractère du buffer
                if (!buffer.isEmpty()) {
                    buffer.chop(1);  // Supprime le dernier caractère du buffer
                    ui->lineEdit->setText(buffer);  // Met à jour le QLineEdit avec le buffer modifié
                    qDebug() << "Buffer after *: " << buffer;  // Debug: Affiche le buffer après la suppression
                }
            } else if (!c.isSpace()) {
                // Si le caractère n'est pas un espace, on l'ajoute au buffer
                buffer.append(c);
                ui->lineEdit->setText(buffer);  // Met à jour le QLineEdit avec le buffer actuel
            }
        }
    }
}*/



/*void ArduinoDialog::readFromArduino() {
    QByteArray data = arduino->read_from_arduino();
    if (!data.isEmpty()) {
        QString receivedText = QString::fromUtf8(data);  // Convertit les données en texte
        for (const QChar &c : receivedText) {
            if (c == '#') {
                // Si on rencontre le caractère '#', on récupère l'ID du buffer
                QString id = buffer.trimmed();  // Enlève les espaces superflus
                ui->lineEdit->setText(id);  // Affiche l'ID dans le QLineEdit
                searchInDatabase(id);  // Recherche l'ID dans la base de données
                buffer.clear();  // Réinitialise le buffer pour le prochain ID
            } else if (c == '*') {
                // Si on rencontre '*', on enlève le dernier caractère du buffer
                if (!buffer.isEmpty()) {
                    buffer.chop(1);  // Supprime le dernier caractère du buffer
                    ui->lineEdit->setText(buffer);  // Met à jour le QLineEdit avec le buffer modifié
                    qDebug() << "Buffer after *: " << buffer;  // Debug: Affiche le buffer après la suppression
                }
            } else if (!c.isSpace()) {
                // Si le caractère n'est pas un espace, on l'ajoute au buffer
                buffer.append(c);
                ui->lineEdit->setText(buffer);  // Met à jour le QLineEdit avec le buffer actuel
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
}*/
