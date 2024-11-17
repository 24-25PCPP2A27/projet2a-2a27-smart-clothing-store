#ifndef QRCODEDIALOG_H
#define QRCODEDIALOG_H

#include <QDialog>
#include <QPixmap>
#include "qrcodegen.h"  // Inclure la bibliothèque QR code

namespace Ui {
class QRCodeDialog;
}

class QRCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QRCodeDialog(QWidget *parent = nullptr);
    ~QRCodeDialog();

private slots:
    void on_pushButton_generate_clicked();  // Slot pour la génération du code QR

private:
    Ui::QRCodeDialog *ui;

    QPixmap generateQRCode(const QString &data);  // Fonction auxiliaire pour générer un QR code
    QString getFournisseurDataByID(const QString &id);  // Récupérer les données du fournisseur par ID
};

#endif // QRCODEDIALOG_H

