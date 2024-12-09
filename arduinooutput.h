#ifndef ARDUINOOUTPUT_H
#define ARDUINOOUTPUT_H

#include <QSerialPort>
#include <QSerialPortInfo>

class ArduinoOutput
{
public:
    ArduinoOutput();
    int connectArduino();
    void sendDataToArduino(const QByteArray &data);
private:
    QSerialPort serial;
    static const quint16 arduinoVendorId = 0x2341;
    static const quint16 arduinoProductId = 0x0043;
};

#endif // ARDUINOOUTPUT_H
