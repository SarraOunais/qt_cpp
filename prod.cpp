#include "prod.h"
#include <QDate>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <string>
#include <QPdfWriter>
#include <QPainter>

prod::prod()
{
    ID_PRODUIT=0;
        NOM="";
        IMAGE="";
        DISPONIBILITE="";
        DISCRIPTION="";
        MATIERE_PREMIERE="";
        CATEGORIE="";
}
 prod::prod(int ID_PRODUIT,QString NOM,QString IMAGE,QString DISPONIBILITE,QString DISCRIPTION,QString MATIERE_PREMIERE,QString CATEGORIE)

{this->ID_PRODUIT=ID_PRODUIT;this->NOM=NOM;this->IMAGE=IMAGE;this->DISPONIBILITE=DISPONIBILITE;this->DISCRIPTION=DISCRIPTION;this->MATIERE_PREMIERE=MATIERE_PREMIERE;this->CATEGORIE=CATEGORIE;}
int prod::getID_PRODUIT(){return ID_PRODUIT;}
QString prod::getNOM(){return NOM;}
      QString prod::getIMAGE(){return IMAGE;}
           QString prod::getDISPONIBILITE(){return DISPONIBILITE;}
                 QString prod::getDISCRIPTION(){return DISCRIPTION;}
                       QString prod::getMATIERE_PREMIERE(){return MATIERE_PREMIERE;}
                            QString prod::getCATEGORIE(){return CATEGORIE;}

void prod::setID_PRODUIT(int ID_PRODUIT){this->ID_PRODUIT=ID_PRODUIT;}
    void prod::setNOM(QString NOM){this->NOM=NOM;}
       void prod::setIMAGE(QString IMAGE){this->IMAGE=IMAGE;}
           void prod::setDISPONIBILITE(QString DISPONIBILITE){this->DISPONIBILITE=DISPONIBILITE;}
              void prod::setDISCRIPTION(QString DISCRIPTION){this->DISCRIPTION=DISCRIPTION;}
                      void prod::setMATIERE_PREMIERE(QString MATIERE_PREMIERE){this->MATIERE_PREMIERE=MATIERE_PREMIERE;}
                         void prod::setCATEGORIE(QString CATEGORIE){this->CATEGORIE=CATEGORIE;}

bool prod::ajouter()
{
    QSqlQuery query;
    QString ID_PRODUIT_string=QString::number(ID_PRODUIT);


         query.prepare("INSERT INTO TABLE_PRODUITS (ID_PRODUIT, NOM,IMAGE,DISPONIBILITE,DISCRIPTION,MATIERE_PREMIERE,CATEGORIE) "
                                                         "VALUES (:ID_PRODUIT,:NOM,:IMAGE,:DISPONIBILITE,:DISCRIPTION,:MATIERE_PREMIERE,:CATEGORIE)");
         query.bindValue(":ID_PRODUIT",ID_PRODUIT_string);
         query.bindValue(":NOM",NOM);
         query.bindValue(":IMAGE",IMAGE);
         query.bindValue(":DISPONIBILITE",DISPONIBILITE);
         query.bindValue(":DISCRIPTION",DISCRIPTION);
         query.bindValue(":MATIERE_PREMIERE",MATIERE_PREMIERE);
         query.bindValue(":CATEGORIE",CATEGORIE);

         return query.exec();

}

QSqlQueryModel* prod::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT* FROM TABLE_PRODUITS");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PRODUIT"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("IMAGE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DISPONIBILITE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DISCRIPTION"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("MATIERE_PREMIERE"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("CATEGORIE"));




    return model;
};

bool prod::supprimer(int ID_PRODUIT){
    QSqlQuery query;
    QString res = QString::number(ID_PRODUIT);
    query.prepare("DELETE FROM TABLE_PRODUITS WHERE ID_PRODUIT=:ID_PRODUIT");
    query.bindValue(":ID_PRODUIT", res);
    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;  // No rows were affected
    }
    return true;
}
bool prod::modifier(int ID_PRODUIT,QString NOM,QString IMAGE,QString DISPONIBILITE,QString DISCRIPTION,QString MATIERE_PREMIERE,QString CATEGORIE)
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM TABLE_PRODUITS WHERE ID_PRODUIT = :ID_PRODUIT");
         query.bindValue(":ID_PRODUIT", ID_PRODUIT);
         query.exec();
         query.next();
         int count = query.value(0).toInt();
         if (count == 0) {
             // ID_C n'existe plus dans la BD ->retour false
             return false;
         }

         // ID_C existe , on execute la modification
         QString ID_PRODUIT_string = QString::number(ID_PRODUIT);
         query.prepare("UPDATE TABLE_PRODUITS SET NOM = COALESCE(:NOM, NOM), IMAGE = COALESCE(:IMAGE, IMAGE), DISPONIBILITE = COALESCE(:DISPONIBILITE, DISPONIBILITE), DISCRIPTION = COALESCE(:DISCRIPTION, DISCRIPTION), MATIERE_PREMIERE = COALESCE(:MATIERE_PREMIERE, MATIERE_PREMIERE),CATEGORIE = COALESCE(:CATEGORIE, CATEGORIE) WHERE ID_PRODUIT = :ID_PRODUIT");
         query.bindValue(":ID_PRODUIT", ID_PRODUIT_string);
         query.bindValue(":NOM", NOM.isEmpty() ? QVariant(QVariant::String) : NOM);
         query.bindValue(":IMAGE", IMAGE.isEmpty() ? QVariant(QVariant::String) : IMAGE);
         query.bindValue(":DISPONIBILITE", DISPONIBILITE.isEmpty() ? QVariant(QVariant::String) : DISPONIBILITE);
         query.bindValue(":DISCRIPTION", DISCRIPTION.isEmpty() ? QVariant(QVariant::String) : DISCRIPTION);
         query.bindValue(":MATIERE_PREMIERE", MATIERE_PREMIERE.isEmpty() ? QVariant(QVariant::String) : MATIERE_PREMIERE);
         query.bindValue(":CATEGORIE", CATEGORIE.isEmpty() ? QVariant(QVariant::String) : CATEGORIE);

         return query.exec();
}
