#include "mainwindowarticles.h"
#include "ui_mainwindowarticles.h"
#include "article.h"
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QVariant>
#include <QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTableView>

MainWindowArticles::MainWindowArticles(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowArticles),
    currentImageIndex(0)
{
    ui->setupUi(this);

    // Connect UI signals to corresponding slots
    connect(ui->pushButton_Ajouter, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Ajouter_clicked);
    connect(ui->pushButton_Modifier, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Modifier_clicked);
    connect(ui->pushButton_Afficher, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Afficher_clicked);
    connect(ui->pushButton_Trier, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Trier_clicked);
    connect(ui->pushButton_Vendre, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Vendre_clicked);
    connect(ui->pushButton_Exporter, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Exporter_clicked);
    connect(ui->pushButton_Image, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Image_clicked);
    connect(ui->lineEdit_Rechercher, &QLineEdit::textChanged, this, &MainWindowArticles::searchArticles); // Search functionality

    connect(ui->stat, &QPushButton::clicked, this, &MainWindowArticles::on_stat_clicked);

    // Initialize components
    connect(ui->pushButton_Next, &QPushButton::clicked, this, &MainWindowArticles::showNextImage);
    connect(ui->pushButton_Previous, &QPushButton::clicked, this, &MainWindowArticles::showPreviousImage);
    connect(ui->pushButton_Refresh, &QPushButton::clicked, this, &MainWindowArticles::refreshCatalog);

    refreshCatalog();
}


MainWindowArticles::~MainWindowArticles()
{
    delete ui;
}

void MainWindowArticles::on_pushButton_Ajouter_clicked()
{
    int IDA = ui->lineEdit_IDa->text().toInt();
    QString TYPE = ui->lineEdit_Type->text();
    QString COULEUR = ui->lineEdit_Couleur->text();
    int QUANTITE = ui->spinBox_Quantite->value();
    float PRIX_UNITAIRE = ui->doubleSpinBox_PrixUnitaire->value();
    QString MARQUE = ui->lineEdit_Marque->text();

    // Create the article with the selected image
    Article article(IDA, TYPE, COULEUR, QUANTITE, PRIX_UNITAIRE, 0, MARQUE, selectedImage);

    if (article.AjouterAritcle()) {
        QMessageBox::information(this, "Success", "Article added successfully.");
        selectedImage.clear(); // Clear the selected image after successful addition
    } else {
        QMessageBox::critical(this, "Error", "Failed to add article.");
    }
}

void MainWindowArticles::on_pushButton_Modifier_clicked()
{
    int IDA = ui->lineEdit_IDa->text().toInt();
    QString TYPE = ui->lineEdit_Type->text();
    QString COULEUR = ui->lineEdit_Couleur->text();
    int QUANTITE = ui->spinBox_Quantite->value();
    float PRIX_UNITAIRE = ui->doubleSpinBox_PrixUnitaire->value();
    QString MARQUE = ui->lineEdit_Marque->text();

    // Use the selected image in the modification
    Article article(IDA, TYPE, COULEUR, QUANTITE, PRIX_UNITAIRE, 0, MARQUE, selectedImage);

    if (article.ModifierAritcle()) {
        QMessageBox::information(this, "Success", "Article modified successfully.");
        selectedImage.clear(); // Clear the selected image after successful modification
    } else {
        QMessageBox::critical(this, "Error", "Failed to modify article.");
    }
}


void MainWindowArticles::on_stat_clicked()
{
    QMap<QString, double> stats; // To store MARQUE and its percentage of total sales
    QSqlQuery query;

    // Query to calculate the total NBR_VENTES for each MARQUE
    QString sql = "SELECT MARQUE, SUM(NBR_VENTES) AS total_sales FROM ARTICLES GROUP BY MARQUE";

    if (!query.exec(sql)) {
        qWarning() << "Error executing query:" << query.lastError().text();
        return;
    }

    double totalSales = 0; // To calculate the total NBR_VENTES for all MARQUES

    // Fetch results and calculate the total sales
    while (query.next()) {
        QString marque = query.value("MARQUE").toString();
        double sales = query.value("total_sales").toDouble();
        stats[marque] = sales;
        totalSales += sales;
    }

    if (stats.isEmpty() || totalSales == 0) {
        qWarning() << "No data found for statistics or total sales is zero!";
        return;
    }

    // Calculate the percentage for each MARQUE
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        stats[it.key()] = (it.value() / totalSales) * 100; // Convert to percentage
    }

    // Create a dialog for the statistics
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistics");
    dialog->resize(600, 400);

    // Create a chart series for the pie chart
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Article Sales Percentage by MARQUE");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->setLayout(layout);

    dialog->exec(); // Show the dialog
}
void MainWindowArticles::on_pushButton_Afficher_clicked()
{
    Article article;
    QSqlQueryModel *model = article.AfficherArticle();
    ui->tableView->setModel(model);
}

void MainWindowArticles::on_pushButton_Vendre_clicked()
{
    int IDA = ui->lineEdit_IDa_vendu->text().toInt();
    int numberToSell = ui->spinBox_Vendre->value();
    QSqlQuery query;
    query.prepare("SELECT QUANTITE, NBR_VENTES FROM ARTICLES WHERE IDA = :IDA");
    query.bindValue(":IDA", IDA);
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve article data: " + query.lastError().text());
        return;
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Error", "Article with the specified ID does not exist.");
        return;
    }
    int currentQuantity = query.value("QUANTITE").toInt();
    int currentSales = query.value("NBR_VENTES").toInt();
    if (numberToSell > currentQuantity) {
        QMessageBox::warning(this, "Insufficient Quantity", "Not enough quantity available to sell.");
        return;
    }
    int newQuantity = currentQuantity - numberToSell;
    int newSales = currentSales + numberToSell;
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE ARTICLES SET QUANTITE = :newQuantity, NBR_VENTES = :newSales WHERE IDA = :IDA");
    updateQuery.bindValue(":newQuantity", newQuantity);
    updateQuery.bindValue(":newSales", newSales);
    updateQuery.bindValue(":IDA", IDA);
    if (updateQuery.exec()) {
        QMessageBox::information(this, "Success", "Article sold successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to update article data: " + updateQuery.lastError().text());
    }
}

void MainWindowArticles::on_pushButton_Exporter_clicked()
{
    Article article;
    QString filePath = QFileDialog::getSaveFileName(this, "Save as PDF", "", "*.pdf");
    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
            filePath.append(".pdf");
        }

        if (article.ExporterPDF(filePath)) {
            QMessageBox::information(this, "Export PDF", "Data successfully exported to PDF.");
        } else {
            QMessageBox::critical(this, "Export PDF", "Failed to export data to PDF.");
        }
    }
}

void MainWindowArticles::searchArticles(const QString &query)
{
    Article article;
    QSqlQueryModel *model = article.RechercherArticle(query); // Search by TYPE
    ui->tableView->setModel(model);
}

void MainWindowArticles::on_pushButton_Trier_clicked()
{
    Article article;
    QSqlQueryModel *model = article.TrierArticles();

    if (model != nullptr) {
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Error", "Failed to sort data.");
    }
}

void MainWindowArticles::on_pushButton_Image_clicked()
{
    // Open a file dialog to select an image
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, tr("No Image Selected"), tr("Please select a valid image file."));
        return;
    }

    // Load the image data into a QByteArray
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to open image file."));
        return;
    }

    // Save image to a member variable (for later use in add or modify)
    selectedImage = file.readAll();
    file.close();

    QMessageBox::information(this, tr("Image Loaded"), tr("Image has been loaded successfully."));
}


void MainWindowArticles::on_pushButton_Supprimer_clicked()
{
    Article article;
    int IDA = ui->lineEdit_IDa_supprime->text().toInt();

    if (article.SupprimerArticle()) {
        QMessageBox::information(this, "Success", "Article deleted successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to delete article.");
    }
}

void MainWindowArticles::displayImage(int index) {
    if (index >= 0 && index < imageCatalog.size()) {
        QPixmap pixmap;
        pixmap.loadFromData(imageCatalog[index]);
        ui->label_ImageDisplay->setPixmap(pixmap.scaled(ui->label_ImageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindowArticles::showNextImage() {
    if (!imageCatalog.isEmpty()) {
        currentImageIndex = (currentImageIndex + 1) % imageCatalog.size();
        displayImage(currentImageIndex);
    }
}

void MainWindowArticles::showPreviousImage() {
    if (!imageCatalog.isEmpty()) {
        currentImageIndex = (currentImageIndex - 1 + imageCatalog.size()) % imageCatalog.size();
        displayImage(currentImageIndex);
    }
}

void MainWindowArticles::refreshCatalog() {
    QSqlQuery query;
    if (!query.exec("SELECT IMAGE FROM ARTICLES")) {
        QMessageBox::critical(this, "Error", "Failed to load images: " + query.lastError().text());
        return;
    }

    imageCatalog.clear();
    while (query.next()) {
        imageCatalog.append(query.value(0).toByteArray());
    }

    if (!imageCatalog.isEmpty()) {
        currentImageIndex = 0;
        displayImage(currentImageIndex);
    } else {
        ui->label_ImageDisplay->clear();
        QMessageBox::information(this, "No Images", "No images found in the database.");
    }
}


