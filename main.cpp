#include "GestClients.h"
#include "connection.h"
#include <QApplication>
#include<QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    bool test=c.createconnection();
    GestClients w;
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                    QObject::tr("Connection successful\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("Database is not open"),
                    QObject::tr("Connection failed\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    return a.exec();
}
