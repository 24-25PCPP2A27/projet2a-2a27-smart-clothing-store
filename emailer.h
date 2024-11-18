#ifndef EMAILER_H
#define EMAILER_H

#include <QObject>
#include <QSslSocket>
#include <QString>
#include <QTextStream>
class MainWindow;
class emailer : public QObject
{
    Q_OBJECT

public:
    emailer(const QString &user, const QString &pass, const QString &host, int port, int timeout);
    ~emailer();
    explicit emailer(QObject *parent = nullptr);


    void sendMail(const QString &from, const QString &to, const QString &subject, const QString &body);
    void sendEmailNotification(const QString &message);
    signals:
        void status(const QString &status);

private slots:
    void connected();
    void readyRead();
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState socketState);

private:
    QString user;  // Email user (login)
    QString pass;  // Email password
    QString host;  // SMTP host (e.g., smtp.gmail.com)
    int port;      // SMTP port (e.g., 465 for SSL)
    int timeout;   // Timeout for connection
    QSslSocket *socket;   // The socket for communication
    QTextStream *t;  // Text stream to write data to the socket
    QString message;
    QString from;
    QString rcpt;
    QString response;
    enum State { Init, HandShake, Auth, User, Pass, Mail, Rcpt, Data, Body, Quit, Close };
    State state;
};

#endif // EMAILER_H
