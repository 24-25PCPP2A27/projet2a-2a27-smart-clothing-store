#ifndef ARDUINO_INPUT_CLAVIER_H
#define ARDUINO_INPUT_CLAVIER_H

#include <QObject> // Nécessaire pour signaux/slots
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class arduino_input_clavier : public QObject
{
    Q_OBJECT // Nécessaire pour signaux/slots

public:
    arduino_input_clavier();
    QString getarduino_port_name();
    QSerialPort *getserial();
    int connect_arduino();
    int close_arduino();
    QByteArray read_from_arduino();
    void write_to_arduino(QByteArray d);

private:
    QString data;
    QString arduino_port_name;
    bool arduino_is_available;
    QSerialPort *serial;

private slots:
    void processReceivedData(); // Déclarez le slot ici
};

#endif // ARDUINO_INPUT_CLAVIER_H
