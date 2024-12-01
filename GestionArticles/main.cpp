#include "mainwindowarticles.h"
#include <QApplication>
#include <QMessageBox>
#include "connectionarticles.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectionArticles ca;
    bool test=ca.createconnect();
    MainWindowArticles w;
    if (test){
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),QObject::tr("connection successful.\n"
                                                                                       "Click Cancel to exit."),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("database is open"), QObject::tr("connection failed.\n"
                                                                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
    return a.exec();
}
