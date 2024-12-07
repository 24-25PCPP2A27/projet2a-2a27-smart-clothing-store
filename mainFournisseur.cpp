#include "mainFournisseur.h"
#include "ui_mainFournisseur.h"
#include "fournisseurs.h"
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QVariant>
#include <QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTableView>
#include "logviewer.h"
#include "arduinodialog.h"
#include "arduino.h"
#include <QTimer>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>
#include <QtMath> // Pour qDegreesToRadians
#include <QVariantList>
#include "connection.h"
#include "gestclients.h"
#include "mainwindow.h"


mainFournisseur::mainFournisseur(QWidget *parent)
    : QMainWindow(parent)

    , ui(new Ui::mainFournisseur)
{
    ui->setupUi(this);
    ui->tableView->setModel(fournisseur.afficher());
    connect(ui->PDF, &QPushButton::clicked, this, &mainFournisseur::exportDataToPDF);
    connect(ui->tri, &QPushButton::clicked, this, &mainFournisseur::on_tri_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &mainFournisseur::on_openLogViewerButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &mainFournisseur::on_openArduinoDialogButton_clicked);
    connect(ui->openMailButton, &QPushButton::clicked, this, &mainFournisseur::on_openMailButton_clicked);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &mainFournisseur::onStatButtonClicked); // Appeler la fonction périodiquement
    timer->start(500); // Rafraîchissement toutes les 1 secondes
    ui->pageFournisseur->setEnabled(false);













    // Connexion du bouton de recherche
    connect(ui->lineEdit, &QLineEdit::returnPressed, [this]() {
        // Récupérer le texte du champ de recherche
        QString query = ui->lineEdit->text();

        // Appeler la méthode de recherche en passant la requête
        searchFournisseurs(query);

    });



    };





mainFournisseur::~mainFournisseur()
{
    delete ui;
    if (mailWidget) {
        delete mailWidget;
        mailWidget = nullptr;  // Avoid dangling pointer
    }
}


void mainFournisseur::handleEmailStatus(const QString &status)
{
    QMessageBox::information(this, "Email Status", status);
}
// Dans mainFournisseur.cpp

/*void mainFournisseur::on_addButton_clicked()
{
    int IDF = ui->idInput->text().toInt();
    if (IDF == 0 && ui->idInput->text() != "0") {
        QMessageBox::warning(this, "Invalid Input", "IDF must be a valid number.");
        return;
    }

    QString NOM = ui->nomInput->text();
    QString PRENOM = ui->prenomInput->text();
    QString ADRESSE = ui->adresseInput->text();
    QString NUM_TEL = ui->numTelInput->text();
    QString CATEGORIE_PROD = ui->comboBox_categorie->currentText();
    int ANCIENNETE = ui->ancienneteInput->text().toInt();
    QString EMAIL = ui->emailInput->text(); // Correct field for email.

    qDebug() << "Form values: IDF=" << IDF << ", NOM=" << NOM << ", PRENOM=" << PRENOM
             << ", ADRESSE=" << ADRESSE << ", NUM_TEL=" << NUM_TEL
             << ", CATEGORIE_PROD=" << CATEGORIE_PROD << ", ANCIENNETE=" << ANCIENNETE
             << ", EMAIL=" << EMAIL;

    Fournisseurs fournisseurs(IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE, EMAIL);

    if (fournisseurs.ajouter()) {
        QMessageBox::information(this, "Success", "Supplier added successfully.");
        LogViewer::writeLog("Add Supplier: Added supplier " + NOM + " " + PRENOM);
    } else {
        QMessageBox::critical(this, "Error", "Failed to add supplier.");
    }
}*/



void mainFournisseur::on_addButton_clicked() {
    int IDF = ui->idInput->text().toInt();
    if (IDF == 0 && ui->idInput->text() != "0") {
        QMessageBox::warning(this, "Invalid Input", "IDF must be a valid number.");
        return;
    }

    QString NOM = ui->nomInput->text();
    QString PRENOM = ui->prenomInput->text();
    QString ADRESSE = ui->adresseInput->text();
    QString NUM_TEL = ui->numTelInput->text();
    QString CATEGORIE_PROD = ui->comboBox_categorie->currentText();
    int ANCIENNETE = ui->ancienneteInput->text().toInt();
    QString EMAIL = ui->emailInput->text();

    Fournisseurs fournisseurs(IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE, EMAIL);

    if (fournisseurs.ajouter()) {
        QMessageBox::information(this, "Success", "Supplier added successfully.");
        LogViewer::writeLog("Add Supplier: Added supplier " + NOM + " " + PRENOM);

        // Rafraîchir les statistiques après l'ajout
        onStatButtonClicked();
    } else {
        QMessageBox::critical(this, "Error", "Failed to add supplier.");
    }
}



void mainFournisseur::on_modifyButton_clicked()
{
    int IDF = ui->idInput->text().toInt();
    QString NOM = ui->nomInput->text();
    QString PRENOM = ui->prenomInput->text();
    QString ADRESSE = ui->adresseInput->text();
    QString NUM_TEL = ui->numTelInput->text();
    QString CATEGORIE_PROD = ui->comboBox_categorie->currentText();
    int ANCIENNETE = ui->ancienneteInput->text().toInt();
    QString EMAIL = ui->emailInput->text();

    Fournisseurs fournisseur(IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE, EMAIL);

    if (fournisseur.modifier()) {
        QMessageBox::information(this, "Success", "Supplier modified successfully.");
        LogViewer::writeLog("Modify Supplier: Modified supplier " + NOM + " " + PRENOM);
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify supplier.");
    }
}

void mainFournisseur::on_displayButton_clicked()
{
    QSqlQueryModel *model = fournisseur.afficher();
    ui->tableView->setModel(model);
}
void mainFournisseur::on_supprimer_Button_2_clicked()
{
    int IDF = ui->idInput->text().toInt();

    if (fournisseur.supprimer(IDF)) {
        QMessageBox::information(this, "Success", "Supplier deleted successfully.");
        LogViewer::writeLog("Delete Supplier: Deleted supplier with ID: " + QString::number(IDF));
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete supplier.");
    }
}






void mainFournisseur::searchFournisseurs(const QString &query)
{
    // Appel de la méthode search() de la classe Fournisseurs
    QSqlQueryModel *model = fournisseur.search(query);  // Utilisation de l'objet 'fournisseur'

    // Mise à jour du modèle dans la vue
    ui->tableView->setModel(model);  // tableView est le nom du widget de la vue
}






void mainFournisseur::initializeCategoryComboBox() {
    // Exemple d'ajout de catégories de produit dans le QComboBox
    ui->comboBox_categorie->addItem("Vetementes");
    ui->comboBox_categorie->addItem("accessoires");
    ui->comboBox_categorie->addItem("chausseures");
    ui->comboBox_categorie->addItem("produits cosmetiques");
    // Ajoutez ici toutes les catégories possibles.
}


/*void mainFournisseur::onStatButtonClicked() {
    static QMap<QString, int> lastStats; // Stocker les dernières statistiques

    // Générer les statistiques actuelles
    QMap<QString, int> currentStats;
    QSqlQuery query;
    QString sql = "SELECT CATEGORIE_PROD, COUNT(*) AS count FROM Fournisseurs GROUP BY CATEGORIE_PROD";

    if (!query.exec(sql)) {
        qWarning() << "Error executing query:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString category = query.value("CATEGORIE_PROD").toString();
        int count = query.value("count").toInt();
        currentStats[category] = count;
    }

    if (currentStats == lastStats) {
        // Si les statistiques n'ont pas changé, ne pas rafraîchir
        return;
    }

    lastStats = currentStats; // Mettre à jour les statistiques sauvegardées

    // Supprimer les anciens widgets du layout de la frame
    if (ui->frame->layout()) {
        QLayoutItem *item;
        while ((item = ui->frame->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }

    // Créer un graphique avec les nouvelles statistiques
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for (auto it = currentStats.begin(); it != currentStats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des fournisseurs par catégorie de produits");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Ajouter le graphique à la frame
    QVBoxLayout *layout = new QVBoxLayout(ui->frame);
    layout->addWidget(chartView);
    ui->frame->setLayout(layout);
}
*/

void mainFournisseur::onStatButtonClicked() {
    static QMap<QString, int> lastStats; // Stocker les dernières statistiques

    // Générer les statistiques actuelles
    QMap<QString, int> currentStats;
    QSqlQuery query;
    QString sql = "SELECT CATEGORIE_PROD, COUNT(*) AS count FROM Fournisseurs GROUP BY CATEGORIE_PROD";

    if (!query.exec(sql)) {
        qWarning() << "Error executing query:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString category = query.value("CATEGORIE_PROD").toString();
        int count = query.value("count").toInt();
        currentStats[category] = count;
    }

    if (currentStats == lastStats) {
        // Si les statistiques n'ont pas changé, ne pas recréer le graphique
        return;
    }

    lastStats = currentStats; // Mettre à jour les statistiques sauvegardées

    // Vérifier s'il y a déjà un layout et le supprimer correctement
    QLayout *existingLayout = ui->frame->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            delete item->widget(); // Supprimer les widgets associés
            delete item;           // Supprimer l'élément du layout
        }
        delete existingLayout;     // Supprimer le layout lui-même
    }

    // Créer un graphique avec les nouvelles statistiques
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for (auto it = currentStats.begin(); it != currentStats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des fournisseurs par catégorie de produits");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Ajouter le graphique à la frame avec un nouveau layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    ui->frame->setLayout(layout);
}










void mainFournisseur::exportDataToPDF() {
    // Open file dialog to choose save location for the PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer en tant que PDF", "", "*.pdf");
    if (!filePath.isEmpty()) {
        // Ensure the file ends with .pdf
        if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
            filePath.append(".pdf");
        }

        // Assuming etmp is an instance of Fournisseurs
        if (fournisseur.exportToPDF(filePath)) {
            QMessageBox::information(this, QObject::tr("Export PDF"),
                                     QObject::tr("Données exportées avec succès en PDF."));
        } else {
            QMessageBox::critical(this, QObject::tr("Erreur d'export PDF"),
                                  QObject::tr("Échec de l'exportation des données en PDF."));
        }
    }

}






void mainFournisseur::on_tri_clicked() {
    // Get the sorted model from the Fournisseurs class
    QSqlQueryModel *model = fournisseur.sortByAnciennete();

    // Check if the model is valid before setting it to the table view
    if (model != nullptr) {
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Error", "Failed to sort data.");
    }
}





void mainFournisseur::on_openLogViewerButton_clicked()
{
    LogViewer logViewer;
    logViewer.exec();
}






void mainFournisseur::on_openArduinoDialogButton_clicked()
{
    // Assurez-vous que vous avez une instance d'Arduino initialisée
    ArduinoDialog dialog(this, &arduino); // Passer l'instance Arduino à ArduinoDialog
    dialog.exec();  // Afficher le dialogue
}
// Déclaration de la fonction
void mainFournisseur::on_openMailButton_clicked() {
    mail *mailDialog = new mail(this); // Create the dialog with this as the parent
    mailDialog->setWindowTitle("Send Email"); // Optional: Set dialog title
    mailDialog->setModal(true); // Make it modal
    mailDialog->exec(); // Open the dialog
    delete mailDialog; // Clean up after the dialog is closed
}  // <- Cette accolade ferme la fonction

// Vérifiez qu'aucune autre fonction n'a des accolades non fermées au-dessus de celle-ci

// Fin de la classe mainFournisseur
 // <- Cette accolade ferme la classe mainFournisseur

void mainFournisseur::on_pageClient_clicked()
{      this->close();
    // Créer une nouvelle instance de l'interface GestClients
    GestClients *clientsWindow = new GestClients(this);

    // Rendre la fenêtre GestClients modale (bloquante)
    clientsWindow->setWindowModality(Qt::ApplicationModal);

    // Afficher la fenêtre clients
    clientsWindow->show();

    // Ne pas fermer mainFournisseur ici. La fenêtre reste ouverte, mais non interactive.

}

void mainFournisseur::on_pageLivraison_clicked()
{     this->close();
    // Créer une nouvelle instance de l'interface GestClients
    MainWindow *livraisonWindow = new MainWindow(this);

    // Rendre la fenêtre GestClients modale (bloquante)
    livraisonWindow->setWindowModality(Qt::ApplicationModal);

    // Afficher la fenêtre clients
    livraisonWindow->show();

    // Ne pas fermer mainFournisseur ici. La fenêtre reste ouverte, mais non interactive.

}
