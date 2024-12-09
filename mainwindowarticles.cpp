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
#include <QSerialPort>
#include <QSerialPortInfo>
#include "arduinooutput.h"
#include <QModelIndex>
#include <QAbstractItemModel>
#include "mainFournisseur.h"
#include "mainwindow.h"
#include "gestclients.h"

MainWindowArticles::MainWindowArticles(QWidget *parent)
    : ui(new Ui::MainWindowArticles),
    currentImageIndex(0)
{
    ui->setupUi(this);

    // Connect UI signals to corresponding slots
//    connect(ui->pushButton_Ajouter, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Ajouter_clicked);
//    connect(ui->pushButton_Modifier, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Modifier_clicked);
    connect(ui->pushButton_Afficher, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Afficher_clicked);
    connect(ui->pushButton_Trier, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Trier_clicked);
    //connect(ui->pushButton_Vendre, &QPushButton::released, this, &MainWindowArticles::on_pushButton_Vendre_released);
    connect(ui->pushButton_Exporter, &QPushButton::clicked, this, &MainWindowArticles::on_pushButton_Exporter_clicked);
    //connect(ui->pushButton_Image, &QPushButton::released, this, &MainWindowArticles::on_pushButton_Image_released);
    connect(ui->lineEdit_Rechercher, &QLineEdit::textChanged, this, &MainWindowArticles::searchArticles); // Search functionality

    connect(ui->stat, &QPushButton::clicked, this, &MainWindowArticles::on_stat_clicked);

    // Initialize components
    connect(ui->pushButton_Next, &QPushButton::clicked, this, &MainWindowArticles::showNextImage);
    connect(ui->pushButton_Previous, &QPushButton::clicked, this, &MainWindowArticles::showPreviousImage);
    connect(ui->pushButton_Refresh, &QPushButton::clicked, this, &MainWindowArticles::refreshCatalog);

    refreshCatalog();
    QSqlQueryModel *model = Atmp.AfficherArticle();
    ui->tableView->setModel(model);
    ui->pageArticle->setEnabled(false);



    int connectionStatus = arduino.connectArduino();
    if (connectionStatus == 0) {
        qDebug() << "Arduino successfully connected!";
    }
    else {
        qDebug() << "Failed to connect Arduino.";
    }
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

    QString TAILLE = ui->lineEdit_Taille->text();  // Get TAILLE from UI

    Article article(IDA, TYPE, TAILLE, COULEUR, QUANTITE, PRIX_UNITAIRE, 0, MARQUE, selectedImage);

    if (article.AjouterAritcle()) {
        QMessageBox::information(this, "Success", "Article added successfully.");
        //selectedImage.clear(); // Clear the selected image after successful addition

        QSqlQueryModel *model = Atmp.AfficherArticle();
        ui->tableView->setModel(model);
       ui->label_ImageDisplay->clear();

    } else {
        QMessageBox::critical(this, "Error", "Failed to add article.");
    }
}

//void MainWindowArticles::on_pushButton_Modifier_clicked()
//{
//    int IDA = ui->lineEdit_IDa->text().toInt();
//    QString TYPE = ui->lineEdit_Type->text();
//    QString COULEUR = ui->lineEdit_Couleur->text();
//    int QUANTITE = ui->spinBox_Quantite->value();
//    float PRIX_UNITAIRE = ui->doubleSpinBox_PrixUnitaire->value();
//    QString MARQUE = ui->lineEdit_Marque->text();
//    QString TAILLE = ui->lineEdit_Taille->text();  // Get TAILLE from UI

//    Article article(IDA, TYPE, TAILLE, COULEUR, QUANTITE, PRIX_UNITAIRE, 0, MARQUE, selectedImage);
//    if (article.ModifierAritcle()) {
//        QMessageBox::information(this, "Success", "Article modified successfully.");
//        selectedImage.clear(); // Clear the selected image after successful modification
//    } else {
//        QMessageBox::critical(this, "Error", "Failed to modify article.");
//    }
//}


void MainWindowArticles::on_pushButton_Modifier_clicked()
{

    // Get IDA from the input field
    int IDA = ui->lineEdit_IDa->text().toInt();

    // Set IDA in the Article object
    Atmp.setIDA(IDA);

    // Call SupprimerArticle with the IDA set
    if (Atmp.SupprimerArticle()) {

        int IDA = ui->lineEdit_IDa->text().toInt();
        QString TYPE = ui->lineEdit_Type->text();
        QString COULEUR = ui->lineEdit_Couleur->text();
        int QUANTITE = ui->spinBox_Quantite->value();
        float PRIX_UNITAIRE = ui->doubleSpinBox_PrixUnitaire->value();
        QString MARQUE = ui->lineEdit_Marque->text();

        QString TAILLE = ui->lineEdit_Taille->text();  // Get TAILLE from UI

        Article article(IDA, TYPE, TAILLE, COULEUR, QUANTITE, PRIX_UNITAIRE, 0, MARQUE, selectedImage);

        if (article.AjouterAritcle()) {
            QMessageBox::information(this, "Success", "Article modified successfully.");
            QSqlQueryModel *model = Atmp.AfficherArticle();
            ui->tableView->setModel(model);
            //selectedImage.clear(); // Clear the selected image after successful addition
        } else {
            QMessageBox::critical(this, "Error", "Failed to modify article.");
        }


    } else {
        QMessageBox::critical(this, "Error", "Failed to modify article.");
    }

 }













void MainWindowArticles::on_pushButton_Afficher_clicked()
{
    QSqlQueryModel *model = Atmp.AfficherArticle();
    ui->tableView->setModel(model);
}

void MainWindowArticles::on_pushButton_Vendre_released()
{
    int IDA = ui->lineEdit_IDa->text().toInt();
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
        QSqlQueryModel *model = Atmp.AfficherArticle();
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Error", "Failed to update article data: " + updateQuery.lastError().text());
    }
}


void MainWindowArticles::on_pushButton_Exporter_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save as PDF", "", "*.pdf");
    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
            filePath.append(".pdf");
        }

        if (Atmp.ExporterPDF(filePath)) {
            QMessageBox::information(this, "Export PDF", "Data successfully exported to PDF.");
        } else {
            QMessageBox::critical(this, "Export PDF", "Failed to export data to PDF.");
        }
    }
}

void MainWindowArticles::searchArticles(const QString &query)
{
    QSqlQueryModel *model = Atmp.RechercherArticle(query); // Search by TYPE
    ui->tableView->setModel(model);
}

void MainWindowArticles::on_pushButton_Trier_clicked()
{
    QSqlQueryModel *model = Atmp.TrierArticles();

    if (model != nullptr) {
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Error", "Failed to sort data.");
    }
}

void MainWindowArticles::on_pushButton_Image_released()
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

    QPixmap pixmap;
    pixmap.loadFromData(selectedImage);
    ui->label_ImageDisplay->setPixmap(pixmap.scaled(ui->label_ImageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //QMessageBox::information(this, tr("Image Loaded"), tr("Image has been loaded successfully."));
}










void MainWindowArticles::on_pushButton_Supprimer_clicked()
{

    // Create a message box
    QMessageBox messageBox;
    messageBox.setWindowTitle("Confirmation");
    messageBox.setText("Do you want to delete?");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No); // Optional: set default button

    // Execute the message box and capture the result
    int result = messageBox.exec();

    // Check the result
    if (result == QMessageBox::Yes) {



        // Get IDA from the input field
        int IDA = ui->lineEdit_IDa->text().toInt();

        // Set IDA in the Article object
        Atmp.setIDA(IDA);

        // Call SupprimerArticle with the IDA set
        if (Atmp.SupprimerArticle()) {
            QMessageBox::information(this, "Success", "Article deleted successfully.");

            QSqlQueryModel *model = Atmp.AfficherArticle();
            ui->tableView->setModel(model);
            ui->label_ImageDisplay->clear();

        } else {
            QMessageBox::critical(this, "Error", "Failed to delete article.");
        }




    } else if (result == QMessageBox::No) {
        qDebug() << "User clicked No";
    }

}

void MainWindowArticles::displayImage(int index) {
    if (index >= 0 && index < imageCatalog.size()) {
        QPixmap pixmap;
        if (pixmap.loadFromData(imageCatalog[index])) {
            ui->label_ImageDisplay->setPixmap(pixmap.scaled(ui->label_ImageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            QMessageBox::critical(this, "Error", "Failed to display image at index: " + QString::number(index));
        }
    } else {
        QMessageBox::critical(this, "Error", "Invalid image index: " + QString::number(index));
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

void MainWindowArticles::on_stat_clicked() {
    static QMap<QString, double> lastStats; // Store the last statistics
    // Generate the current statistics
    QMap<QString, double> currentStats;
    QSqlQuery query;
    QString sql = "SELECT MARQUE, SUM(NBR_VENTES) AS total_sales FROM ARTICLES GROUP BY MARQUE";

    /*if (!query.exec(sql)) {
        qWarning() << "Error executing query:" << query.lastError().text();
        return;
    }*/
    if (!query.exec(sql)) {
        qWarning() << "Error executing query after switching interfaces:" << query.lastError().text();
        return;
    }


    double totalVentes = 0;
    QMap<QString, double> salesByMarque;

    // Calculate total sales and individual sales by MARQUE
    while (query.next()) {
        QString marque = query.value("MARQUE").toString();
        double totalSalesForMarque = query.value("total_sales").toDouble();
        salesByMarque[marque] = totalSalesForMarque;
        totalVentes += totalSalesForMarque;
    }

    if (totalVentes == 0) {
        QMessageBox::information(this, "No Data", "No sales data available for statistics.");
        return;
    }

    // Calculate the percentage of sales for each MARQUE
    for (auto it = salesByMarque.begin(); it != salesByMarque.end(); ++it) {
        currentStats[it.key()] = (it.value() / totalVentes) * 100.0;
    }

    if (currentStats == lastStats) {
        // If the statistics have not changed, do not refresh
        return;
    }

    lastStats = currentStats; // Update the saved statistics

    // Remove the old widgets from the layout of the frame
/*    if (ui->frame->layout()) {
        QLayoutItem *item;
        while ((item = ui->frame->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    }*/
    if (ui->frame->layout()) {
        QLayoutItem *item;
        while ((item = ui->frame->layout()->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater(); // Use deleteLater for proper cleanup
            }
            delete item;
        }
    }


    // Create a pie chart with the new statistics
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for (auto it = currentStats.begin(); it != currentStats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistics of Articles by MARQUE (Percentage of Sales)");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the chart to the frame
    QVBoxLayout *layout = new QVBoxLayout(ui->frame);
    layout->addWidget(chartView);
//    ui->frame->setLayout(layout);
    if (!ui->frame->layout()) {
        QVBoxLayout *newLayout = new QVBoxLayout(ui->frame);
        ui->frame->setLayout(newLayout);
    }
}


/*void MainWindowArticles::on_pushButton_CheckStock_clicked()
{
    int articleID = ui->lineEdit_IDM->text().toInt();
    qDebug() << "Checking stock for article ID:" << articleID;

    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database connection is not open!";
        arduino.sendDataToArduino("Error: Database connection closed\n");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT QUANTITE FROM ARTICLES WHERE IDA = :IDA");
    query.bindValue(":IDA", articleID);

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
        arduino.sendDataToArduino("Error: Database query failed\n");
        return;
    }

    if (query.next()) {
        int quantity = query.value(0).toInt();
        qDebug() << "Quantity found for ID" << articleID << ":" << quantity;
        QString message = (quantity > 0) ? QString("Stock: %1").arg(quantity) : "Out of stock";
        arduino.sendDataToArduino(message.toUtf8());
    } else {
        qDebug() << "No results found for ID:" << articleID;
        arduino.sendDataToArduino("Error: ID not found\n");
    }
}*/















void MainWindowArticles::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) {
        qDebug() << "Invalid index!";
        return;
    }
    // Get the model associated with the table view
    QAbstractItemModel *model = ui->tableView->model();
    if (!model) {
        qDebug() << "No model set for the table view!";
        return;
    }
    // Retrieve the data from the model using the index
    int IDA = model->data(index).toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM ARTICLES WHERE IDA = :IDA");
    query.bindValue(":IDA", IDA);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve article data: " + query.lastError().text());
        return;
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Error", "Article with the specified ID does not exist.");
        return;
    }




    ui->lineEdit_IDa->setText(QString::number(IDA));

    QString vvv = query.value("TYPE").toString();
    ui->lineEdit_Type->setText(vvv);

    vvv = query.value("TAILLE").toString();
    ui->lineEdit_Taille->setText(vvv);

    vvv = query.value("COULEUR").toString();
    ui->lineEdit_Couleur->setText(vvv);

    vvv = query.value("MARQUE").toString();
    ui->lineEdit_Marque->setText(vvv);



    int vtmp = query.value("QUANTITE").toInt();
    ui->spinBox_Quantite->setValue(vtmp);

    float vprix = query.value("PRIX_UNITAIRE").toFloat();
    ui->doubleSpinBox_PrixUnitaire->setValue(vprix);



    QPixmap pixmap;
    pixmap.loadFromData(query.value("IMAGE").toByteArray());
    ui->label_ImageDisplay->setPixmap(pixmap.scaled(ui->label_ImageDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));



}

void MainWindowArticles::on_pageFournisseur_clicked()
{     this->close();
    // Créer une nouvelle instance de l'interface GestClients
    mainFournisseur *fournisseurWindow = new mainFournisseur(this);

    // Rendre la fenêtre GestClients modale (bloquante)
    fournisseurWindow->setWindowModality(Qt::ApplicationModal);

    // Afficher la fenêtre clients
    fournisseurWindow->show();

    // Ne pas fermer mainFournisseur ici. La fenêtre reste ouverte, mais non interactive.

}
void MainWindowArticles::on_pageLivraison_clicked()
{   this->close();
    // Créer une nouvelle instance de l'interface GestClients
    MainWindow *livraisonWindow = new MainWindow(this);

    // Rendre la fenêtre GestClients modale (bloquante)
    livraisonWindow->setWindowModality(Qt::ApplicationModal);

    // Afficher la fenêtre clients
    livraisonWindow->show();

    // Ne pas fermer mainFournisseur ici. La fenêtre reste ouverte, mais non interactive.

}

void MainWindowArticles::on_pageClient_clicked()
{      this->close();
    // Créer une nouvelle instance de l'interface GestClients
    GestClients *clientsWindow = new GestClients(this);

    // Rendre la fenêtre GestClients modale (bloquante)
    clientsWindow->setWindowModality(Qt::ApplicationModal);

    // Afficher la fenêtre clients
    clientsWindow->show();

    // Ne pas fermer mainFournisseur ici. La fenêtre reste ouverte, mais non interactive.

}


