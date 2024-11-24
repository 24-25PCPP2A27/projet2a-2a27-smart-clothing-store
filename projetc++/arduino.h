#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino
{
public:
    Arduino();
    QString getArduinoPortName();
    QSerialPort* getSerial();
    int connectArduino();
    int closeArduino();
    QByteArray readFromArduino();
    int writeToArduino(QByteArray data);

private:
    QSerialPort* serial;
    QString arduino_port_name;
    bool arduino_is_available;

    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
};

#endif // ARDUINO_H
