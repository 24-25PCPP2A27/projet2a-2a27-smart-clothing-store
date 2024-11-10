#include "emailer.h"
#include <QSslSocket>
#include <QTextStream>
#include <QDebug>

emailer::emailer(const QString &user, const QString &pass, const QString &host, int port, int timeout)
    : user(user), pass(pass), host(host), port(port), timeout(timeout), state(Init)
{
    socket = new QSslSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError))); // Old-style connection
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
}

emailer::~emailer()
{
    delete socket;
    delete t;
}

void emailer::sendEmailNotification(const QString &message)
{
    this->message = message;

    // Simulate sending an email (you would replace this with actual SMTP communication logic)
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        socket->connectToHostEncrypted(host, port);
        qDebug() << "Attempting to connect to the SMTP server...";
    }
}

void emailer::connected()
{
    // When connected to the server, we initiate the email sending process
    qDebug() << "Connected to SMTP server. Sending email...";

    // You can add your SMTP commands here (HELO, AUTH LOGIN, MAIL FROM, RCPT TO, DATA, etc.)
    // For simplicity, we will print the message content.
    qDebug() << "Email content: " << message;

    // Simulate successful sending by moving to the next step
    state = Body;
    qDebug() << "Email sent successfully.";
    socket->disconnectFromHost();
}

void emailer::readyRead()
{
    response = socket->readAll();
    qDebug() << "Server Response: " << response;
}

void emailer::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Error: " << socketError;
    // You can add more detailed error handling based on socketError if needed
}

void emailer::disconnected()
{
    qDebug() << "Disconnected from SMTP server.";
}

void emailer::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket State: " << socketState;
    // Handle different socket states if needed
    if (socketState == QAbstractSocket::ConnectedState) {
        // Perform necessary steps after connection is established
    } else if (socketState == QAbstractSocket::UnconnectedState) {
        // Perform necessary steps when disconnected
    }
}
