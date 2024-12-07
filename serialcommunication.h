#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QtSerialPort/QSerialPort>
#include <QDebug>

class SerialCommunication : public QObject
{
    Q_OBJECT
public:
    explicit SerialCommunication(QObject *parent = nullptr);
    ~SerialCommunication();

    void connectToArduino();  // Establish connection with Arduino
    void sendBuzzerCommand();  // Send command to trigger the buzzer
       void readFromArduino(); // Function to read data from Arduino
    void disconnectFromArduino();  // Disconnect from Arduino

signals:
     void statusChangeRequested();

private:
    QSerialPort serialPort;

};

#endif // SERIALCOMMUNICATION_H
