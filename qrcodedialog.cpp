#include "qrcodedialog.h"
#include "ui_qrcodedialog.h"
#include "qrcodedialog.h"
#include "ui_qrcodedialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>

QRCodeDialog::QRCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRCodeDialog)
{
    ui->setupUi(this);
}

QRCodeDialog::~QRCodeDialog()
{
    delete ui;
}

// Slot pour la génération du code QR
void QRCodeDialog::on_pushButton_generate_clicked()
{
    QString id = ui->lineEdit_ID->text();  // Récupérer l'ID du fournisseur à partir de l'input

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID de fournisseur.");
        return;
    }

    // Récupérer les données du fournisseur à partir de la base de données
    QString fournisseurData = getFournisseurDataByID(id);
    if (fournisseurData.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucun fournisseur trouvé avec l'ID donné.");
        return;
    }

    // Générer le code QR pour les données du fournisseur
    QPixmap qrPixmap = generateQRCode(fournisseurData);

    // Afficher le code QR dans le label
    ui->label_QRCode->setPixmap(qrPixmap);
}

// Récupérer les données du fournisseur par ID depuis la base de données
QString QRCodeDialog::getFournisseurDataByID(const QString &id)
{
    QSqlQuery query;
    query.prepare("SELECT IDF, NOM, PRENOM, ADRESSE, CATEGORIE_PROD, NUM_TEL FROM FOURNISSEURS WHERE IDF = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec de la requête à la base de données : " + query.lastError().text());
        return QString();
    }

    if (query.next()) {
        QString fournisseurData = QString("ID: %1\nNom: %2 %3\nAdresse: %4\nCatégorie de produit: %5\nNuméro de téléphone: %6")
                               .arg(query.value("ID").toString())
                               .arg(query.value("NOM").toString())
                               .arg(query.value("PRENOM").toString())
                               .arg(query.value("ADRESSE").toString())
                               .arg(query.value("CATEGORIE_PROD").toString())
                               .arg(query.value("NUM_TEL").toString());
        return fournisseurData;
    }

    return QString();  // Retourner une chaîne vide si aucun fournisseur n'est trouvé
}

// Fonction auxiliaire pour générer un code QR
QPixmap QRCodeDialog::generateQRCode(const QString &data)
{
    using namespace qrcodegen;

    QrCode qr = QrCode::encodeText(data.toUtf8().constData(), QrCode::Ecc::LOW);
    const int size = qr.getSize();

    QImage image(size, size, QImage::Format_RGB32);
    image.fill(Qt::white);  // Remplir l'arrière-plan de blanc

    // Dessiner le code QR
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            QColor color = qr.getModule(x, y) ? Qt::black : Qt::white;
            image.setPixelColor(x, y, color);
        }
    }

    // Redimensionner le code QR pour une meilleure visibilité
    return QPixmap::fromImage(image.scaled(200, 200, Qt::KeepAspectRatio));
}

