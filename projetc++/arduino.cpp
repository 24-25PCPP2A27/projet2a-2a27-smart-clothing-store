#include "arduino.h"
#include <QDebug>

Arduino::Arduino()
{
    serial = new QSerialPort;
    arduino_port_name = "";
    arduino_is_available = false;
}

QString Arduino::getArduinoPortName()
{
    return arduino_port_name;
}

QSerialPort* Arduino::getSerial()
{
    return serial;
}

int Arduino::connectArduino()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.hasVendorIdentifier() && info.hasProductIdentifier()) {
            if (info.vendorIdentifier() == arduino_uno_vendor_id &&
                info.productIdentifier() == arduino_uno_product_id) {
                arduino_is_available = true;
                arduino_port_name = info.portName();
            }
        }
    }

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QIODevice::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;
        }
        return 1;
    }
    return -1;
}

QByteArray Arduino::readFromArduino()
{
    if (serial->isReadable())
        return serial->readAll();
    return QByteArray();
}

int Arduino::writeToArduino(QByteArray data)
{
    if (serial->isWritable()) {
        serial->write(data);
        return 0;
    }
    return 1;
}
