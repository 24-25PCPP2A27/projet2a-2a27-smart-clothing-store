/********************************************************************************
** Form generated from reading UI file 'mainwindowarticles.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWARTICLES_H
#define UI_MAINWINDOWARTICLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowArticles
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit_IDa;
    QLineEdit *lineEdit_Type;
    QLineEdit *lineEdit_Couleur;
    QSpinBox *spinBox_Quantite;
    QDoubleSpinBox *doubleSpinBox_PrixUnitaire;
    QLineEdit *lineEdit_Marque;
    QTableView *tableView;
    QSpinBox *spinBox_Vendre;
    QPushButton *pushButton_Exporter;
    QPushButton *pushButton_Vendre;
    QLineEdit *lineEdit_IDa_vendu;
    QLineEdit *lineEdit_IDa_supprime;
    QPushButton *pushButton_Supprimer;
    QPushButton *pushButton_Ajouter;
    QPushButton *pushButton_Afficher;
    QPushButton *pushButton_Modifier;
    QPushButton *stat;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *pushButton_Trier;
    QLineEdit *lineEdit_Rechercher;
    QPushButton *pushButton_Image;
    QLabel *label_11;
    QLabel *label_ImageDisplay;
    QPushButton *pushButton_Previous;
    QPushButton *pushButton_Next;
    QPushButton *pushButton_Refresh;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowArticles)
    {
        if (MainWindowArticles->objectName().isEmpty())
            MainWindowArticles->setObjectName(QStringLiteral("MainWindowArticles"));
        MainWindowArticles->resize(1270, 629);
        QPalette palette;
        QBrush brush(QColor(3, 52, 149, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(174, 228, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(106, 156, 253, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush3(QColor(254, 229, 225, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush3);
        QBrush brush4(QColor(255, 184, 208, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush2);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush5(QColor(3, 52, 149, 128));
        brush5.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush5);
#endif
        MainWindowArticles->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Verdana"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        MainWindowArticles->setFont(font);
        centralwidget = new QWidget(MainWindowArticles);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        lineEdit_IDa = new QLineEdit(centralwidget);
        lineEdit_IDa->setObjectName(QStringLiteral("lineEdit_IDa"));
        lineEdit_IDa->setGeometry(QRect(180, 30, 151, 41));
        lineEdit_Type = new QLineEdit(centralwidget);
        lineEdit_Type->setObjectName(QStringLiteral("lineEdit_Type"));
        lineEdit_Type->setGeometry(QRect(180, 90, 151, 41));
        lineEdit_Couleur = new QLineEdit(centralwidget);
        lineEdit_Couleur->setObjectName(QStringLiteral("lineEdit_Couleur"));
        lineEdit_Couleur->setGeometry(QRect(180, 150, 151, 41));
        spinBox_Quantite = new QSpinBox(centralwidget);
        spinBox_Quantite->setObjectName(QStringLiteral("spinBox_Quantite"));
        spinBox_Quantite->setGeometry(QRect(180, 210, 151, 41));
        doubleSpinBox_PrixUnitaire = new QDoubleSpinBox(centralwidget);
        doubleSpinBox_PrixUnitaire->setObjectName(QStringLiteral("doubleSpinBox_PrixUnitaire"));
        doubleSpinBox_PrixUnitaire->setGeometry(QRect(180, 270, 151, 41));
        lineEdit_Marque = new QLineEdit(centralwidget);
        lineEdit_Marque->setObjectName(QStringLiteral("lineEdit_Marque"));
        lineEdit_Marque->setGeometry(QRect(180, 330, 151, 41));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(740, 80, 501, 331));
        spinBox_Vendre = new QSpinBox(centralwidget);
        spinBox_Vendre->setObjectName(QStringLiteral("spinBox_Vendre"));
        spinBox_Vendre->setGeometry(QRect(440, 340, 51, 41));
        pushButton_Exporter = new QPushButton(centralwidget);
        pushButton_Exporter->setObjectName(QStringLiteral("pushButton_Exporter"));
        pushButton_Exporter->setGeometry(QRect(420, 500, 171, 41));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../Downloads/download-pdf_6348573.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Exporter->setIcon(icon);
        pushButton_Exporter->setIconSize(QSize(28, 28));
        pushButton_Vendre = new QPushButton(centralwidget);
        pushButton_Vendre->setObjectName(QStringLiteral("pushButton_Vendre"));
        pushButton_Vendre->setGeometry(QRect(500, 340, 131, 41));
        lineEdit_IDa_vendu = new QLineEdit(centralwidget);
        lineEdit_IDa_vendu->setObjectName(QStringLiteral("lineEdit_IDa_vendu"));
        lineEdit_IDa_vendu->setGeometry(QRect(480, 290, 151, 41));
        lineEdit_IDa_supprime = new QLineEdit(centralwidget);
        lineEdit_IDa_supprime->setObjectName(QStringLiteral("lineEdit_IDa_supprime"));
        lineEdit_IDa_supprime->setGeometry(QRect(830, 430, 131, 41));
        pushButton_Supprimer = new QPushButton(centralwidget);
        pushButton_Supprimer->setObjectName(QStringLiteral("pushButton_Supprimer"));
        pushButton_Supprimer->setGeometry(QRect(970, 430, 191, 41));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../../../../Downloads/remove_7695824.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Supprimer->setIcon(icon1);
        pushButton_Supprimer->setIconSize(QSize(28, 28));
        pushButton_Ajouter = new QPushButton(centralwidget);
        pushButton_Ajouter->setObjectName(QStringLiteral("pushButton_Ajouter"));
        pushButton_Ajouter->setGeometry(QRect(50, 440, 131, 41));
        pushButton_Afficher = new QPushButton(centralwidget);
        pushButton_Afficher->setObjectName(QStringLiteral("pushButton_Afficher"));
        pushButton_Afficher->setGeometry(QRect(1110, 30, 131, 41));
        pushButton_Modifier = new QPushButton(centralwidget);
        pushButton_Modifier->setObjectName(QStringLiteral("pushButton_Modifier"));
        pushButton_Modifier->setGeometry(QRect(200, 440, 131, 41));
        stat = new QPushButton(centralwidget);
        stat->setObjectName(QStringLiteral("stat"));
        stat->setGeometry(QRect(50, 500, 221, 41));
        QIcon icon2;
        icon2.addFile(QStringLiteral("../../../../Downloads/market-penetration_15178126.png"), QSize(), QIcon::Normal, QIcon::Off);
        stat->setIcon(icon2);
        stat->setIconSize(QSize(28, 28));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1150, 450, 141, 141));
        label->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/received_545354601345279.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 30, 141, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 90, 141, 41));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 150, 141, 41));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 210, 141, 41));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(50, 270, 141, 41));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(50, 330, 141, 41));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(440, 290, 81, 41));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(790, 430, 81, 41));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(420, 440, 301, 71));
        pushButton_Trier = new QPushButton(centralwidget);
        pushButton_Trier->setObjectName(QStringLiteral("pushButton_Trier"));
        pushButton_Trier->setGeometry(QRect(980, 30, 121, 41));
        QIcon icon3;
        icon3.addFile(QStringLiteral("../../../../Downloads/swap_5296648.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Trier->setIcon(icon3);
        pushButton_Trier->setIconSize(QSize(28, 28));
        lineEdit_Rechercher = new QLineEdit(centralwidget);
        lineEdit_Rechercher->setObjectName(QStringLiteral("lineEdit_Rechercher"));
        lineEdit_Rechercher->setGeometry(QRect(790, 30, 181, 41));
        pushButton_Image = new QPushButton(centralwidget);
        pushButton_Image->setObjectName(QStringLiteral("pushButton_Image"));
        pushButton_Image->setGeometry(QRect(50, 380, 201, 41));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(740, 30, 41, 41));
        label_11->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/search_4180975.png")));
        label_11->setScaledContents(true);
        label_ImageDisplay = new QLabel(centralwidget);
        label_ImageDisplay->setObjectName(QStringLiteral("label_ImageDisplay"));
        label_ImageDisplay->setGeometry(QRect(410, 30, 251, 181));
        label_ImageDisplay->setLayoutDirection(Qt::LeftToRight);
        pushButton_Previous = new QPushButton(centralwidget);
        pushButton_Previous->setObjectName(QStringLiteral("pushButton_Previous"));
        pushButton_Previous->setGeometry(QRect(410, 220, 41, 41));
        pushButton_Next = new QPushButton(centralwidget);
        pushButton_Next->setObjectName(QStringLiteral("pushButton_Next"));
        pushButton_Next->setGeometry(QRect(620, 220, 41, 41));
        pushButton_Refresh = new QPushButton(centralwidget);
        pushButton_Refresh->setObjectName(QStringLiteral("pushButton_Refresh"));
        pushButton_Refresh->setGeometry(QRect(460, 220, 151, 41));
        MainWindowArticles->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowArticles);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1270, 26));
        MainWindowArticles->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowArticles);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowArticles->setStatusBar(statusbar);

        retranslateUi(MainWindowArticles);

        QMetaObject::connectSlotsByName(MainWindowArticles);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowArticles)
    {
        MainWindowArticles->setWindowTitle(QApplication::translate("MainWindowArticles", "MainWindowArticles", Q_NULLPTR));
        pushButton_Exporter->setText(QApplication::translate("MainWindowArticles", "Exporter", Q_NULLPTR));
        pushButton_Vendre->setText(QApplication::translate("MainWindowArticles", "Vendre", Q_NULLPTR));
        pushButton_Supprimer->setText(QApplication::translate("MainWindowArticles", "Supprimer", Q_NULLPTR));
        pushButton_Ajouter->setText(QApplication::translate("MainWindowArticles", "Ajouter", Q_NULLPTR));
        pushButton_Afficher->setText(QApplication::translate("MainWindowArticles", "Afficher", Q_NULLPTR));
        pushButton_Modifier->setText(QApplication::translate("MainWindowArticles", "Modifier", Q_NULLPTR));
        stat->setText(QApplication::translate("MainWindowArticles", "Top Marques", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindowArticles", "ID", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindowArticles", "Type", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindowArticles", "Couleur", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindowArticles", "Quantit\303\251", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindowArticles", "Prix", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindowArticles", "Marque", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindowArticles", "ID", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindowArticles", "ID", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindowArticles", "Liste des articles epuis\303\251s", Q_NULLPTR));
        pushButton_Trier->setText(QApplication::translate("MainWindowArticles", "Trier", Q_NULLPTR));
        pushButton_Image->setText(QApplication::translate("MainWindowArticles", "Ajouter Image", Q_NULLPTR));
        label_11->setText(QString());
        label_ImageDisplay->setText(QApplication::translate("MainWindowArticles", "Image", Q_NULLPTR));
        pushButton_Previous->setText(QApplication::translate("MainWindowArticles", "<", Q_NULLPTR));
        pushButton_Next->setText(QApplication::translate("MainWindowArticles", ">", Q_NULLPTR));
        pushButton_Refresh->setText(QApplication::translate("MainWindowArticles", "Actualiser", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowArticles: public Ui_MainWindowArticles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWARTICLES_H
