#include "GestClients.h"
#include "ui_gestclients.h"
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
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QColor>
#include<QDateTime>

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
    void GestClients::on_stats_clicked()
    {
        // Get client status statistics
        QMap<QString, int> stats = Clients::getStatistiquesByStatus();

        // Create a QGraphicsScene to display the custom bar chart
        QGraphicsScene *scene = new QGraphicsScene();

        // Create a QGraphicsView to display the scene
        QGraphicsView *view = new QGraphicsView(scene);
        view->setWindowTitle("Clients by Status (Bar Chart)");

        // Bar chart settings
        int barWidth = 50;       // Width of each bar
        int maxBarHeight = 200;  // Maximum height of bars
        int spacing = 20;        // Space between bars

        // Calculate the maximum count to scale the bars
        int maxCount = 0;
        for (auto it = stats.begin(); it != stats.end(); ++it) {
            if (it.value() > maxCount) {
                maxCount = it.value();
            }
        }

        // Draw the bars
        int xOffset = 0;  // X position of the first bar
        for (auto it = stats.begin(); it != stats.end(); ++it) {
            QString status = it.key();
            int count = it.value();

            // Scale bar height relative to maxCount
            int barHeight = static_cast<int>((static_cast<double>(count) / maxCount) * maxBarHeight);

            // Create a rectangle (bar) item
            QGraphicsRectItem *bar = scene->addRect(xOffset, maxBarHeight - barHeight, barWidth, barHeight);
            bar->setBrush(QBrush(Qt::blue));  // Set the bar color

            // Add a label for the status under each bar
            QGraphicsTextItem *label = scene->addText(status);
            label->setPos(xOffset, maxBarHeight + 10);

            // Add a label for the count above each bar
            QGraphicsTextItem *countLabel = scene->addText(QString::number(count));
            countLabel->setPos(xOffset + barWidth / 4, maxBarHeight - barHeight - 20);

            // Move to the next bar position
            xOffset += barWidth + spacing;
        }

        // Adjust the scene size to fit all bars
        scene->setSceneRect(0, 0, xOffset, maxBarHeight + 50);

        // Show the graphics view as a standalone window
        view->setScene(scene);
        view->setMinimumSize(xOffset + 50, maxBarHeight + 100);  // Adjust window size
        view->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        view->show();
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

    // Slot pour vérifier l'inactivité d'un client
    void GestClients::on_verifierInactivite_clicked()
    {
        int idcl = ui->idcl->text().toInt();

        clients->verifierInactivite(idcl); // Vérifie l'inactivité
        QMessageBox::information(this, "Vérification d'inactivité", "La vérification d'inactivité a été effectuée.");
    }

    // Slot pour ajouter des points lors d'une commande
    void GestClients::on_ajouterCommandePoints_clicked()
    {
        int idcl = ui->idcl->text().toInt();
        int montantCommande = ui->montantCommande->text().toInt();

        // Ajouter des points correspondant au montant de la commande
        clients->ajouterPoints(idcl, montantCommande);

        QMessageBox::information(this, "Points de fidélité", QString("Le client avec l'ID %1 a reçu %2 points supplémentaires.")
                                 .arg(idcl).arg(montantCommande));
    }
