#include "arduinooutput.h"
#include <QDebug>

ArduinoOutput::ArduinoOutput()
{

}

int ArduinoOutput::connectArduino()
{
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        if (portInfo.hasVendorIdentifier() && portInfo.hasProductIdentifier()) {
            if (portInfo.vendorIdentifier() == arduinoVendorId &&
                portInfo.productIdentifier() == arduinoProductId) {
                serial.setPort(portInfo);
                if (serial.open(QIODevice::WriteOnly)) {
                    serial.setBaudRate(QSerialPort::Baud9600);
                    serial.setDataBits(QSerialPort::Data8);
                    serial.setParity(QSerialPort::NoParity);
                    serial.setStopBits(QSerialPort::OneStop);
                    serial.setFlowControl(QSerialPort::NoFlowControl);
                    return 0; // Success
                }
            }
        }
    }
    return 1; // Failure
}

void ArduinoOutput::sendDataToArduino(const QByteArray &data)
{
    if (serial.isOpen() && serial.isWritable()) {
        serial.write(data);
    } else {
        qDebug() << "Failed to send data to Arduino.";
    }
}
