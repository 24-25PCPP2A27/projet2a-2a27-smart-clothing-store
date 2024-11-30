#include "serialcommunication.h"

SerialCommunication::SerialCommunication(QObject *parent)
    : QObject(parent)
{
}

SerialCommunication::~SerialCommunication() {
    disconnectFromArduino();
}

void SerialCommunication::connectToArduino() {
    serialPort.setPortName("COM5");  // Change this to the correct port
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to Arduino!";
    } else {
        qDebug() << "Failed to connect to Arduino: " << serialPort.errorString();
    }
}

void SerialCommunication::sendBuzzerCommand() {
    if (serialPort.isOpen()) {
        serialPort.write("BUZZER_ON");  // Send the command to activate the buzzer
        qDebug() << "BUZZER_ON command sent to Arduino.";
    } else {
        qDebug() << "Failed to send command: Arduino not connected.";
    }
}
void SerialCommunication::readFromArduino() {
    if (serialPort.canReadLine()) {
        QString command = serialPort.readLine().trimmed();
        if (command == "STATUS_CHANGE") {
            emit statusChangeRequested();  // Emit status change signal
            qDebug() << "STATUS_CHANGE received from Arduino";
        }
    }
}





void SerialCommunication::disconnectFromArduino() {
    if (serialPort.isOpen()) {
        serialPort.close();
        qDebug() << "Disconnected from Arduino";
    }
}
