#include "mail.h"
#include "ui_mail.h"

mail::mail(QWidget *parent) :
    QDialog(parent), // Change from QMainWindow to QDialog
    ui(new Ui::mail)
{
    ui->setupUi(this);
    connect(ui->pbSendEmail, SIGNAL(clicked()), this, SLOT(slot_pbSendEmail()));
    connect(ui->pbAddFiles_2, SIGNAL(clicked()), this, SLOT(slot_AddFiles()));
    connect(ui->pbRemoveFiles_2, SIGNAL(clicked()), this, SLOT(slot_RemoveFiles()));

    ui->lePassword_2->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->pbRemoveFiles_2->setEnabled(false);
    qDebug() << "Mail window initialized.";
}

mail::~mail()
{
    delete ui;
}

void mail::slot_pbSendEmail()
{
    QString str;

    m_emailSender = ui->leSender_2->text();
    m_emailServerPassword = ui->lePassword_2->text();
    m_emailSmtpServer = ui->leSmtpServer_2->text();

    m_emailSenderName = ui->leSenderName_2->text();

    str=ui->teRecipients_2->toPlainText();
    m_emailRecipient = str.split('\n');

    m_emailSubject = ui->leSubject_2->text();

    m_emailMessage=ui->teMessage_2->toPlainText();

    m_smtp = new Smtp(m_emailSender,
                      m_emailServerPassword,
                      m_emailSmtpServer,
                      465,
                      30000);

   connect(m_smtp, SIGNAL(status(QString)), this, SLOT(slot_emailStatus(QString)));

    m_smtp->sendMail(m_emailSender,
                     m_emailSenderName,
                     m_emailRecipient,
                     m_emailSubject,
                     m_emailMessage,
                     m_emailFiles);
}

void mail::slot_emailStatus(QString statusStr)
{
    ui->lStatus->setText(statusStr);
}

void mail::slot_AddFiles()
{
    ui->pbRemoveFiles_2->setEnabled(true);

    m_emailFiles.append(QFileDialog::getOpenFileNames(this, tr("Add files"), ""));

    for(int i = 0; i < m_emailFiles.size(); i++) {
        ui->teFiles_2->append(m_emailFiles.at(i));
    }
}

void mail::slot_RemoveFiles()
{
    m_emailFiles.clear();
    ui->teFiles_2->clear();
    ui->pbRemoveFiles_2->setEnabled(false);
}
