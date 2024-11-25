#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseurs.h"
#include <QMessageBox>
#include "emailer.h"
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(fournisseur.afficher());
    connect(ui->stat_Button, &QPushButton::clicked, this, &MainWindow::onStatButtonClicked);
    connect(ui->PDF, &QPushButton::clicked, this, &MainWindow::exportDataToPDF);
    connect(ui->tri, &QPushButton::clicked, this, &MainWindow::on_tri_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_openLogViewerButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_openArduinoDialogButton_clicked);








    // Create an instance of emailer with login credentials
    emailer *mailer = new emailer("your_email@example.com", "your_password", "smtp.example.com", 465, 5000);

    // Connect emailer status to handleEmailStatus function
    connect(mailer, SIGNAL(status(QString)), this, SLOT(handleEmailStatus(QString)));

    // Connexion du bouton de recherche
    connect(ui->lineEdit, &QLineEdit::returnPressed, [this]() {
        // Récupérer le texte du champ de recherche
        QString query = ui->lineEdit->text();

        // Appeler la méthode de recherche en passant la requête
        searchFournisseurs(query);

    });



    };





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleEmailStatus(const QString &status)
{
    QMessageBox::information(this, "Email Status", status);
}
// Dans mainwindow.cpp

void MainWindow::on_addButton_clicked()
{
    int IDF = ui->idInput->text().toInt();
    QString NOM = ui->nomInput->text();
    QString PRENOM = ui->prenomInput->text();
    QString ADRESSE = ui->adresseInput->text();
    QString NUM_TEL = ui->numTelInput->text();
    QString CATEGORIE_PROD = ui->comboBox_categorie->currentText();
    int ANCIENNETE = ui->ancienneteInput->text().toInt();
    QString EMAIL = ui->ancienneteInput_2->text();

    Fournisseurs fournisseur(IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE, EMAIL);

    if (fournisseur.ajouter()) {
        QMessageBox::information(this, "Success", "Supplier added successfully.");
        LogViewer::writeLog("Add Supplier: Added supplier " + NOM + " " + PRENOM);
    } else {
        QMessageBox::critical(this, "Error", "Failed to add supplier.");
    }
}


void MainWindow::on_modifyButton_clicked()
{
    int IDF = ui->idInput->text().toInt();
    QString NOM = ui->nomInput->text();
    QString PRENOM = ui->prenomInput->text();
    QString ADRESSE = ui->adresseInput->text();
    QString NUM_TEL = ui->numTelInput->text();
    QString CATEGORIE_PROD = ui->comboBox_categorie->currentText();
    int ANCIENNETE = ui->ancienneteInput->text().toInt();
    QString EMAIL = ui->ancienneteInput_2->text();

    Fournisseurs fournisseur(IDF, NOM, PRENOM, ADRESSE, NUM_TEL, CATEGORIE_PROD, ANCIENNETE, EMAIL);

    if (fournisseur.modifier()) {
        QMessageBox::information(this, "Success", "Supplier modified successfully.");
        LogViewer::writeLog("Modify Supplier: Modified supplier " + NOM + " " + PRENOM);
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify supplier.");
    }
}

void MainWindow::on_displayButton_clicked()
{
    QSqlQueryModel *model = fournisseur.afficher();
    ui->tableView->setModel(model);
}
void MainWindow::on_supprimer_Button_2_clicked()
{
    int IDF = ui->idInput->text().toInt();

    if (fournisseur.supprimer(IDF)) {
        QMessageBox::information(this, "Success", "Supplier deleted successfully.");
        LogViewer::writeLog("Delete Supplier: Deleted supplier with ID: " + QString::number(IDF));
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete supplier.");
    }
}






void MainWindow::searchFournisseurs(const QString &query)
{
    // Appel de la méthode search() de la classe Fournisseurs
    QSqlQueryModel *model = fournisseur.search(query);  // Utilisation de l'objet 'fournisseur'

    // Mise à jour du modèle dans la vue
    ui->tableView->setModel(model);  // tableView est le nom du widget de la vue
}






void MainWindow::initializeCategoryComboBox() {
    // Exemple d'ajout de catégories de produit dans le QComboBox
    ui->comboBox_categorie->addItem("Vetementes");
    ui->comboBox_categorie->addItem("accessoires");
    ui->comboBox_categorie->addItem("chausseures");
    ui->comboBox_categorie->addItem("produits cosmetiques");
    // Ajoutez ici toutes les catégories possibles.
}

void MainWindow::onStatButtonClicked() {
    // Generate statistics
    QMap<QString, int> stats;
    QSqlQuery query;
    QString sql = "SELECT CATEGORIE_PROD, COUNT(*) AS count FROM Fournisseurs GROUP BY CATEGORIE_PROD";

    if (!query.exec(sql)) {
        qWarning() << "Error executing query:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString category = query.value("CATEGORIE_PROD").toString();
        int count = query.value("count").toInt();
        stats[category] = count;
    }

    if (stats.isEmpty()) {
        qWarning() << "No data found for statistics!";
        return;
    }

    // Create a dialog for the statistics
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistics");
    dialog->resize(600, 400);

    // Create a chart
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Fournisseurs Statistics by CATEGORIE_PROD");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Create a chart view
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the chart view to the dialog layout
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->setLayout(layout);

    // Show the dialog
    dialog->exec(); // Use exec() for a modal dialog
}






void MainWindow::exportDataToPDF() {
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


void MainWindow::on_tri_clicked() {
    // Get the sorted model from the Fournisseurs class
    QSqlQueryModel *model = fournisseur.sortByAnciennete();

    // Check if the model is valid before setting it to the table view
    if (model != nullptr) {
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Error", "Failed to sort data.");
    }
}





void MainWindow::on_openLogViewerButton_clicked()
{
    LogViewer logViewer;
    logViewer.exec();
}






void MainWindow::on_openArduinoDialogButton_clicked()
{
    // Assurez-vous que vous avez une instance d'Arduino initialisée
    ArduinoDialog dialog(this, &arduino); // Passer l'instance Arduino à ArduinoDialog
    dialog.exec();  // Afficher le dialogue
}












