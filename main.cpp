#include "gestion_produit.h"

#include "connection.h"
#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gestion_produit w;
    connection c;
       bool test=c.createconnect();
       if(test)
       {w.show();
           QMessageBox::information(nullptr, QObject::tr("database is open"),
                       QObject::tr("connection successful.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
       else
           QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                       QObject::tr("connection failed.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);



       return a.exec();
    w.show();
    return a.exec();
}
