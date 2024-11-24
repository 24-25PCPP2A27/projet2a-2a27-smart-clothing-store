#include "arduino_input_clavier.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QObject> // Pour les signaux/slots




arduino_input_clavier::arduino_input_clavier()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString arduino_input_clavier::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *arduino_input_clavier::getserial()
{
   return serial;
}
int arduino_input_clavier::connect_arduino() {
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
            }
        }
    }
    qDebug() << "arduino_port_name is :" << arduino_port_name;
    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            // Connecter le signal readyRead au slot processReceivedData
            connect(serial, &QSerialPort::readyRead, this, &arduino_input_clavier::processReceivedData);

            return 0;
        }
        return 1;
    }
    return -1;
}

int arduino_input_clavier::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


 QByteArray arduino_input_clavier::read_from_arduino()
{
    if(serial->isReadable()){
         data=serial->readAll(); //récupérer les données reçues

         return data;
    }
 }


void arduino_input_clavier::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}


void arduino_input_clavier::processReceivedData() {
    QByteArray receivedData = readAll(); // Lire les données reçues d'Arduino
    qDebug() << "Données reçues : " << receivedData; // Convertir les données en QString

    // Vérifier que l'ID est un nombre valide
    bool isNumeric;
    int articleID = idString.toInt(&isNumeric);

    if (isNumeric) {
        // Rechercher dans la base de données
        QString result = searchArticleInDatabase(articleID);

        // Envoyer le résultat à Arduino
        write_to_arduino(result.toUtf8());
    } else {
        // Si l'ID est invalide, envoyer un message d'erreur
        write_to_arduino("Erreur : ID non valide.\n");
    }
}



QString arduino_input_clavier::searchArticleInDatabase(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Articles WHERE IDA = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche SQL :" << query.lastError().text();
        return "Erreur : Problème de requête SQL.\n";
    }

    if (query.next()) {
        // Construire une chaîne contenant les informations de l'article
        QString result = QString(
            "ID: %1\nQuantité: %2\nMarque: %3\nType: %4\nLongueur: %5\nCouleur: %6\nPrix: %7\nNbr Ventes: %8\nIDF: %9")
                             .arg(query.value("IDA").toString())
                             .arg(query.value("QUANTITE").toString())
                             .arg(query.value("MARQUE").toString())
                             .arg(query.value("TYPE").toString())
                             .arg(query.value("LONGUEUR").toString())
                             .arg(query.value("COULEUR").toString())
                             .arg(query.value("PRIX").toString())
                             .arg(query.value("NBR_VENTE").toString())
                             .arg(query.value("IDF").toString());
        return result;
    } else {
        return "Article non trouvé pour cet ID.\n";
    }
}





