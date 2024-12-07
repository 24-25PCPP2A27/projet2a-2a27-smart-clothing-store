#ifndef MAIL_H
#define MAIL_H

#include <QDialog>
#include <QFileDialog>
#include "smtp.h"

namespace Ui {
class mail;
}

class mail : public QDialog
{
    Q_OBJECT

public:
    explicit mail(QWidget *parent = nullptr);
    ~mail();

private:
    Ui::mail *ui;
    Smtp *m_smtp;

    QString m_emailSender;
    QString m_emailSenderName;
    QString m_emailSmtpServer;
    QString m_emailServerPassword;
    QStringList m_emailRecipient;
    QString m_emailSubject;
    QString m_emailMessage;
    QStringList m_emailFiles;

private slots:
    void slot_pbSendEmail();
    void slot_emailStatus(QString);
    void slot_AddFiles();
    void slot_RemoveFiles();
};

#endif // MAIL_H
