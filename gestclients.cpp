#include "gestclients.h"
#include "ui_GestClients.h"
#include "clients.h"
#include <QMessageBox>
#include<QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QLabel>
#include <QSqlError>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QPieSlice>

#include <QSqlQuery>
#include<QDateTime>
#include <QColor>

GestClients::GestClients(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestClients)
{
    ui->setupUi(this);
    ui->tableView->setModel(Ctmp.afficher());

}

GestClients::~GestClients()
{
    delete ui;
}

// Method to handle adding a new client
void GestClients::on_ajouter_clicked()
{
    int idcl = ui->idcl->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString adresse = ui->adresse->text();
    QString email = ui->email->text();
    QString telephone = ui->telephone->text();
    QString status = ui->status->currentText();
    int anciennete = ui->anciennete->text().toInt();

    // Création dynamique de l'objet clients
    clients = new Clients(idcl, nom, prenom, adresse, email, telephone, status, anciennete);

    // Ajouter le client
    if (clients->ajouter()) {
        QMessageBox::information(this, "Succès", "Client ajouté avec succès et 50 points attribués.");
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur lors de l'ajout du client.");
    }

    // Libérer la mémoire utilisée par clients après utilisation
    delete clients;
    clients = nullptr;

    // Optionnel : Rafraîchir la vue après l'ajout
    ui->tableView->setModel(Ctmp.afficher());
}


// Method to handle deleting a client
void GestClients::on_supprimer_clicked()
{
    int idcl = ui->idcl->text().toInt();
    bool test = Ctmp.supprimer(idcl);

    if (test)
    {
        ui->tableView->setModel(Ctmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression"));
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"), QObject::tr("Suppression non effectuér.\n"), QMessageBox::Cancel);
    }

}

void GestClients::on_modifier_clicked()
{
    int idcl = ui->idcl->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString adresse = ui->adresse->text();
    QString email = ui->email->text();
    QString telephone = ui->telephone->text();
    QString status = ui->status->currentText();
    int anciennete = ui->anciennete->text().toInt();

    Clients C(idcl, nom, prenom, adresse, email, telephone, status, anciennete);

    if (C.modifier())
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Modification effectuée\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(Ctmp.afficher());  // Refresh table view
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Modification non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void GestClients::on_trier_clicked()
{
    // Call the trier method from Ctmp (Clients instance) to sort by ANCIENNETE
    QSqlQueryModel *model = Ctmp.trier(ordreAscendant);

    // Update the table view with the sorted data
    ui->tableView->setModel(model);

    // Toggle the sorting order for the next click
    ordreAscendant = !ordreAscendant;
}
// Slot pour rechercher un client par ID
void GestClients::on_rechercheID_clicked()
{
    int idcl = ui->idcl->text().toInt();
    qDebug() << "Searching for client with ID:" << idcl;  // Log the ID entered by the user

    QSqlQueryModel *model = Ctmp.rechercheID(idcl);

    int rowCount = model->rowCount();
    qDebug() << "Row count returned by query: " << rowCount;  // Log the row count

    if (rowCount == 0) {
        qDebug() << "No client found with ID" << idcl;  // Log when no client is found
        QMessageBox::information(this, "No Results", "No client found with this ID.");
    } else {
        qDebug() << "Displaying data for client:" << idcl;
        ui->tableView->setModel(model);
    }
}
    // Fonction pour exporter les données des clients en pdf
void GestClients::on_pdf_clicked()
{
    // Affichage de la boîte de dialogue pour choisir le chemin de sauvegarde
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous", "C:/Users/lenovo/OneDrive/Desktop/Qt Creator/GestClients/clients_list.html", "HTML Files (*.html)");

    if (filePath.isEmpty()) {
        return;  // Annuler si aucun chemin n'est choisi
    }

    // Créer le fichier HTML
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible de créer le fichier HTML");
        return;
    }

    QTextStream stream(&file);

    // Récupérer les données des clients à partir du modèle (ex : clients->afficher())
    QSqlQueryModel *model = clients->afficher();
    int rowCount = model->rowCount();

    // Écrire le contenu HTML
    stream << "<!DOCTYPE html>\n";
    stream << "<html>\n";
    stream << "<head>\n";
    stream << "<meta charset='UTF-8'>\n";
    stream << "<title>Liste des Clients</title>\n";
    stream << "<style>\n";
    stream << "table { width: 100%; border-collapse: collapse; margin: 20px 0; font-size: 14px; }\n";
    stream << "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }\n";
    stream << "th { background-color: #f2f2f2; }\n";
    stream << "</style>\n";
    stream << "</head>\n";
    stream << "<body>\n";

    // Titre et date actuelle
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    stream << "<h1>Liste des Clients</h1>\n";
    stream << "<p>Date de generation : " + currentDate + "</p>\n";

    // Début du tableau
    stream << "<table>\n";
    stream << "<thead>\n";
    stream << "<tr>\n";
    stream << "<th>ID</th>\n";
    stream << "<th>Nom</th>\n";
    stream << "<th>Adresse</th>\n";
    stream << "<th>Email</th>\n";
    stream << "<th>Téléphone</th>\n";
    stream << "<th>Statut</th>\n";
    stream << "<th>Ancienneté</th>\n";
    stream << "</tr>\n";
    stream << "</thead>\n";
    stream << "<tbody>\n";

    // Remplir le tableau avec les données
    for (int row = 0; row < rowCount; ++row) {
        stream << "<tr>\n";
        stream << "<td>" << model->data(model->index(row, 0)).toString() << "</td>\n"; // ID
        stream << "<td>" << model->data(model->index(row, 1)).toString() << "</td>\n"; // Nom
        stream << "<td>" << model->data(model->index(row, 2)).toString() << "</td>\n"; // Adresse
        stream << "<td>" << model->data(model->index(row, 3)).toString() << "</td>\n"; // Email
        stream << "<td>" << model->data(model->index(row, 4)).toString() << "</td>\n"; // Téléphone
        stream << "<td>" << model->data(model->index(row, 5)).toString() << "</td>\n"; // Statut
        stream << "<td>" << model->data(model->index(row, 6)).toString() << "</td>\n"; // Ancienneté
        stream << "</tr>\n";
    }

    stream << "</tbody>\n";
    stream << "</table>\n";

    // Fin du document HTML
    stream << "</body>\n";
    stream << "</html>\n";

    file.close();


    QMessageBox::information(this, "Fichier Sauvegardé", "HTML sauvegardé à : " + filePath);
}
void GestClients::on_stats_clicked() {
    // Step 1: Fetch statistics from the database
    QMap<QString, int> stats;
    QSqlQuery query;

    // Count active clients
    query.prepare("SELECT COUNT(*) FROM clients WHERE status = 'active'");
    if (query.exec() && query.next()) {
        stats["Active"] = query.value(0).toInt();
        qDebug() << "Active clients:" << stats["Active"]; // Debug output
    } else {
        qDebug() << "Error fetching active clients:" << query.lastError().text();
    }

    // Count inactive clients
    query.prepare("SELECT COUNT(*) FROM clients WHERE status = 'inactive'");
    if (query.exec() && query.next()) {
        stats["Inactive"] = query.value(0).toInt();
        qDebug() << "Inactive clients:" << stats["Inactive"]; // Debug output
    } else {
        qDebug() << "Error fetching inactive clients:" << query.lastError().text();
    }

    // Step 2: Handle empty data
    if (stats.isEmpty() || (stats["Active"] == 0 && stats["Inactive"] == 0)) {
        QMessageBox::information(this, "No Data", "No client data available to display.");
        return;
    }

    // Step 3: Create the pie chart series
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    series->append("Active", stats["Active"]);
    series->append("Inactive", stats["Inactive"]);

    // Step 4: Customize the slices with the new colors
    QtCharts::QPieSlice *activeSlice = series->slices().at(0);
    activeSlice->setLabel(QString("Active (%1 - %2%)")
        .arg(stats["Active"])
        .arg((stats["Active"] * 100) / (stats["Active"] + stats["Inactive"])));
    activeSlice->setBrush(QColor("#FFB8D0")); // Pink color for Active
    activeSlice->setExploded(true);   // Explode (highlight) the active slice
    activeSlice->setLabelVisible(true);

    QtCharts::QPieSlice *inactiveSlice = series->slices().at(1);
    inactiveSlice->setLabel(QString("Inactive (%1 - %2%)")
        .arg(stats["Inactive"])
        .arg((stats["Inactive"] * 100) / (stats["Active"] + stats["Inactive"])));
    inactiveSlice->setBrush(QColor("#033495")); // Blue color for Inactive
    inactiveSlice->setLabelVisible(true);

    // Debug output for slice color assignment
    qDebug() << "Active slice color: " << activeSlice->brush().color().name();
    qDebug() << "Inactive slice color: " << inactiveSlice->brush().color().name();

    // Step 5: Create and configure the chart
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Clients by Status (Active vs Inactive)");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Interactive Legend: Toggle slice exploded state on click
    connect(series, &QtCharts::QPieSeries::clicked, [](QtCharts::QPieSlice *slice) {
        slice->setExploded(!slice->isExploded());
    });

    // Step 6: Create the chart view
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Step 7: Show the chart in a standalone window
    chartView->setMinimumSize(800, 600);
    chartView->setWindowTitle("Client Status Statistics (Pie Chart)");
    chartView->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    chartView->show();
}
// Slot pour calculer les points de fidélité
    void GestClients::on_calculerPointsFidelite_clicked()
    {
        int idcl = ui->idcl->text().toInt();

        // Calculer les points pour le client
        int points = Ctmp.calculerPointsFidelite(idcl);

        // Afficher le résultat
        QMessageBox::information(this, "Points de fidélité",
                                 QString("Le client avec l'ID %1 a %2 points de fidélité.")
                                 .arg(idcl).arg(points));
    }
    void GestClients::on_ajouterCommandePoints_clicked() {
        int idcl = ui->idcl->text().toInt();

        // Check if the client exists
        QSqlQuery queryCheckClient;
        queryCheckClient.prepare("SELECT COUNT(*) FROM clients WHERE idcl = :idcl");
        queryCheckClient.bindValue(":idcl", idcl);

        if (!queryCheckClient.exec() || !queryCheckClient.next() || queryCheckClient.value(0).toInt() == 0) {
            QMessageBox::warning(this, "Error", QString("Client with ID %1 does not exist.").arg(idcl));
            return;
        }

        // Get the total `prix` of all commandes for the client
        QSqlQuery queryPrix;
        queryPrix.prepare(
            "SELECT SUM(commande.prix) "
            "FROM commande "
            "INNER JOIN client_commande ON commande.idco = client_commande.idco "
            "WHERE client_commande.idcl = :idcl");
        queryPrix.bindValue(":idcl", idcl);

        if (!queryPrix.exec() || !queryPrix.next()) {
            QMessageBox::warning(this, "Error", "Failed to retrieve total `prix` for the client.");
            qDebug() << "Database error:" << queryPrix.lastError().text();
            return;
        }

        int totalPrix = queryPrix.value(0).toInt();

        // Calculate the points (e.g., 1 point per 10 units of `prix`)
        int additionalPoints = totalPrix / 10;

        // Update the client's points
        QSqlQuery queryUpdatePoints;
        queryUpdatePoints.prepare("UPDATE clients SET points = points + :additionalPoints WHERE idcl = :idcl");
        queryUpdatePoints.bindValue(":additionalPoints", additionalPoints);
        queryUpdatePoints.bindValue(":idcl", idcl);

        if (!queryUpdatePoints.exec()) {
            QMessageBox::warning(this, "Error", "Failed to update points for the client.");
            qDebug() << "Database error:" << queryUpdatePoints.lastError().text();
            return;
        }

        QMessageBox::information(this, "Points Updated",
                                 QString("Client with ID %1 has been awarded %2 additional points.")
                                 .arg(idcl).arg(additionalPoints));
    }
    // Slot pour vérifier l'inactivité d'un client
    void GestClients::on_verifierInactivite_clicked() {
        int idcl = ui->idcl->text().toInt();

        // Check the client's status
        QSqlQuery queryStatus;
        queryStatus.prepare("SELECT status FROM clients WHERE idcl = :idcl");
        queryStatus.bindValue(":idcl", idcl);

        if (!queryStatus.exec() || !queryStatus.next()) {
            QMessageBox::warning(this, "Error", "Failed to retrieve the client's status.");
            qDebug() << "Database error:" << queryStatus.lastError().text();
            return;
        }

        QString status = queryStatus.value(0).toString();

        // If the client is inactive, reset points
        if (status == "inactive") {
            QSqlQuery queryResetPoints;
            queryResetPoints.prepare("UPDATE clients SET points = 0 WHERE idcl = :idcl");
            queryResetPoints.bindValue(":idcl", idcl);

            if (!queryResetPoints.exec()) {
                QMessageBox::warning(this, "Error", "Failed to reset points for inactive client.");
                qDebug() << "Database error:" << queryResetPoints.lastError().text();
                return;
            }

            QMessageBox::information(this, "Inactivity Check",
                                     QString("Client with ID %1 is inactive. Points have been reset.").arg(idcl));
        } else {
            QMessageBox::information(this, "Inactivity Check",
                                     QString("Client with ID %1 is active. No points were reset.").arg(idcl));
        }
    }
