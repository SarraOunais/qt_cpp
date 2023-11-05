#include "connection.h"
#include <QString>

connection::connection()
{

}

bool connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("gestion_produit");
db.setUserName("jasser");
db.setPassword("0000");

if (db.open())
test=true;





    return  test;
}
