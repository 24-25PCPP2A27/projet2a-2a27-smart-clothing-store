#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "livraisons.h"
#include <QMessageBox>
#include <QDebug>
#include <QTextDocument>
#include <QFileDialog>
#include <QTextCursor>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "barchartwidget.h"




// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    displayLivraisons(); // Display deliveries when the window is created
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_ajouter_clicked()
{
    qDebug() << "Ajouter button clicked.";

    // Retrieve inputs from the UI
    int IDL = ui->lineEdit_IDL->text().toInt();
    QString NUM_TRANSPORTEUR = ui->lineEdit_NUM_TRANSPORTEUR->text().trimmed();
    QString NOM_TRANSPORTEUR = ui->lineEdit_NOM_TRANSPORTEUR->text().trimmed();
    QString ADRESSE_LIV = ui->lineEdit_ADRESSE_LIV->text().trimmed();
    QString STATUE_LIV = ui->lineEdit_STATUE_LIV->text().trimmed();
    int FRAIS_LIV = ui->lineEdit_FRAIS_LIV->text().toInt();
    QDate DATE_LIV = ui->dateEdit_DATE_LIV->date();

    // Validate inputs
    if (NUM_TRANSPORTEUR.isEmpty() || NOM_TRANSPORTEUR.isEmpty() || ADRESSE_LIV.isEmpty() || STATUE_LIV.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        qDebug() << "Empty field detected.";
        return;
    }

    // Create livraison object
    livraisons l(IDL, NUM_TRANSPORTEUR, NOM_TRANSPORTEUR, ADRESSE_LIV, STATUE_LIV, FRAIS_LIV, DATE_LIV);

    // Add the livraison and update the display
    if (l.ajouter()) {
        QMessageBox::information(this, "Success", "Livraison added successfully.");
        displayLivraisons(); // Refresh the list of livraisons
    } else {
        QMessageBox::warning(this, "Error", "Failed to add livraison.");
    }

    qDebug() << "Input validation completed.";
}

void MainWindow::on_pushButton_afficher_clicked()
{
    displayLivraisons();
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    QString idlText = ui->lineEdit->text();  // Get text from the input field
    if (idlText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid IDL to delete.");
        return;
    }

    int IDL = idlText.toInt();  // Convert the input to an integer
    if (IDL <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a positive integer IDL.");
        return;
    }

    qDebug() << "Deleting IDL:" << IDL;  // Debug the IDL value being passed

    livraisons l;
    if (l.supprimer(IDL)) {  // Call supprimer with the entered IDL
        QMessageBox::information(this, "Success", "Livraison deleted successfully.");
        displayLivraisons();  // Refresh the display
        ui->lineEdit_IDL->clear();  // Clear the input field
        ui->lineEdit_IDL->setFocus();  // Refocus on the input field
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete the livraison. Verify the IDL.");
    }
}







void MainWindow::displayLivraisons()
{
    // Debug statement to confirm function call
    qDebug() << "Refreshing display with updated data from SQL table";

    // Clear the current table content and row count
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Call display() to get the latest data
    livraisons l;
    QSqlQueryModel* model = l.display();

    // Set row and column counts based on the model
    int rowCount = model->rowCount();
    int columnCount = model->columnCount();
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(columnCount);

    // Populate the table widget with data from the model
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(model->data(model->index(row, col)).toString());
            ui->tableWidget->setItem(row, col, item);
        }
    }

    // Set the headers for the table widget
    QStringList headers = {"IDL", "NUM_TRANSPORTEUR", "NOM_TRANSPORTEUR", "ADRESSE_LIV", "STATUE_LIV", "FRAIS_LIV", "DATE_LIV"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Force a repaint to refresh the view
    ui->tableWidget->repaint();
}

void MainWindow::on_pushButton_sort_clicked() {
    // Call the tri() function to get the sorted data
    livraisons l;
    QSqlQueryModel* model = l.tri();

    // Clear the tableWidget and populate it with sorted data
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount());

    // Populate the tableWidget with the sorted data
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(data));
        }
    }

    // Set the column headers (adjust as needed based on your table structure)
    QStringList headers = {"IDL", "NUM_TRANSPORTEUR", "NOM_TRANSPORTEUR", "ADRESSE_LIV", "STATUE_LIV", "FRAIS_LIV", "DATE_LIV"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Debugging output to confirm sorting action
    qDebug() << "Data sorted by DATE_LIV in descending order.";
}


void MainWindow::on_pushButton_recherche_clicked() {
    // Get the IDL from the search input field
    int IDL = ui->lineEdit_recherche->text().toInt();
    if (IDL == 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid IDL.");
        return;
    }

    // Use the rechercher function to search for the IDL
    livraisons l;
    QSqlQueryModel* model = l.rechercher(IDL);

    // Check if the model contains any rows
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Results", "No livraison found with the specified IDL.");
        return;
    }

    // Clear the tableWidget and populate it with search results
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount());

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(data));
        }
    }

    // Set the column headers (optional, adjust as needed)
    QStringList headers = {"IDL", "NUM_TRANSPORTEUR", "NOM_TRANSPORTEUR", "ADRESSE_LIV", "STATUE_LIV", "FRAIS_LIV", "DATE_LIV"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}



void MainWindow::on_pushButton_exportPDF_clicked() {
    // Choose the file path
    QString filePath = QFileDialog::getSaveFileName(this, "Save as PDF", "", "*.pdf");
    if (filePath.isEmpty()) {
        return;  // User canceled
    }

    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
        filePath += ".pdf";  // Ensure the file extension is .pdf
    }

    // Start building HTML content
    QString html;
    html += "<h2>Livraisons Table Export</h2>";
    html += "<table border='1' cellspacing='0' cellpadding='4'>";
    html += "<thead><tr>";
    QStringList headers = {"IDL", "NUM_TRANSPORTEUR", "NOM_TRANSPORTEUR", "ADRESSE_LIV", "STATUE_LIV", "FRAIS_LIV", "DATE_LIV"};
    for (const QString &header : headers) {
        html += QString("<th>%1</th>").arg(header);
    }
    html += "</tr></thead>";

    // Populate table rows
    html += "<tbody>";
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QString cellData = ui->tableWidget->item(row, col)->text();
            html += QString("<td>%1</td>").arg(cellData);
        }
        html += "</tr>";
    }
    html += "</tbody></table>";

    // Create a QTextDocument and set the HTML content
    QTextDocument document;
    document.setHtml(html);

    // Export to PDF
    QPrinter printer(QPrinter::PrinterMode::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    document.print(&printer);

    QMessageBox::information(this, "Success", "Table exported as PDF successfully!");
}

//stats:


void MainWindow::on_pushButton_showStats_clicked() {
    // Get address statistics from livraisons
    livraisons l;
    QMap<QString, int> stats = l.getAdresseStats();

    // Create the BarChartWidget and pass the stats data
    BarChartWidget *chartWidget = new BarChartWidget(stats, this);

    // Set the chartWidget as a child of the "frame_chart" in the "Statistics" tab
    QLayout *layout = ui->frame_chart->layout();
    if (!layout) {
        layout = new QVBoxLayout(ui->frame_chart);
        ui->frame_chart->setLayout(layout);
    }

    // Clear any previous content
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();  // Remove the old chart widget
        delete child;
    }

    // Add the new chart widget
    layout->addWidget(chartWidget);
    chartWidget->show();

    // Switch to the "Statistics" tab
    ui->tabwidget->setCurrentWidget(ui->tab_4);  // Ensure to name your tab appropriately
}




