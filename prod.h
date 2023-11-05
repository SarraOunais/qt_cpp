#ifndef PROD_H
#define PROD_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QTableView>
class prod
{

public:
    prod();
prod(int,QString ,QString ,QString ,QString ,QString ,QString );


        int getID_PRODUIT();
          QString getNOM();
           QString getIMAGE();
           QString getDISPONIBILITE();
           QString getDISCRIPTION();
          QString getMATIERE_PREMIERE();
          QString getCATEGORIE();

           void setID_PRODUIT(int);

           void setNOM(QString);

          void setIMAGE(QString);

          void setDISPONIBILITE(QString);

           void setDISCRIPTION(QString);

           void setMATIERE_PREMIERE(QString);

           void setCATEGORIE(QString);

           bool ajouter();
                   QSqlQueryModel* afficher();
                   bool supprimer(int);

                   bool modifier(int,QString,QString,QString,QString,QString,QString);

    private:
     int ID_PRODUIT;
     QString NOM,IMAGE,DISPONIBILITE,DISCRIPTION,MATIERE_PREMIERE,CATEGORIE;

};

#endif // PROD_H
