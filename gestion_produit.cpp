#include "gestion_produit.h"
#include "ui_gestion_produit.h"
#include "prod.h"
#include <vector>
#include <string>
#include <QBuffer>
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include<QDebug>
#include<QImage>
#include <QPixmap>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include<QTextDocument>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrintDialog>
#include <QGraphicsView>
#include <QTabWidget>
//#include <QMediaPlayer>
#include <QSqlQuery>
gestion_produit::gestion_produit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_produit)
{
    ui->setupUi(this);
}

gestion_produit::~gestion_produit()
{
    delete ui;
}


void gestion_produit::on_ajouter_clicked()
{
    QString ID_PRODUIT_string = ui->ID_PRODUIT->text();
         bool ok;
         int ID_PRODUIT = ID_PRODUIT_string.toInt(&ok);
             if (!ok) {
             // ça retourne un message d'erreur en cas ou l'initiative est invalid
             QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for ID.");
             return;
         }

         QString NOM = ui->NOM->text();
         QString IMAGE = ui->IMAGE->text();
         QString DISPONIBILITE = ui->DISPONIBILITE->text();
         QString DISCRIPTION = ui->DISCRIPTION->text();
         QString MATIERE_PREMIERE = ui->MATIERE_PREMIERE->text();
         QString CATEGORIE = ui->CATEGORIE->text();





        prod  tr  (ID_PRODUIT,NOM,IMAGE,DISPONIBILITE,DISCRIPTION,MATIERE_PREMIERE,CATEGORIE);
         bool test = tr.ajouter();

         QMessageBox msgBox;
         if (test) {
             msgBox.setText("ajout avec succes");
             msgBox.exec();
             ui->ID_PRODUIT->clear();
             ui->NOM->clear();
             ui->IMAGE->clear();
             ui->DISPONIBILITE->clear();
             ui->DISCRIPTION->clear();
             ui->MATIERE_PREMIERE->clear();
             ui->CATEGORIE->clear();

         } else {
             msgBox.setText("echec");
             msgBox.exec();
         }

         ui->tableView->setModel(tr.afficher());
}

void gestion_produit::on_modifier_clicked()
{
    int ID_PRODUIT=ui->ID_PRODUIT->text().toInt();
               QString NOM = ui->NOM->text();
                     QString IMAGE = ui->IMAGE->text();
                           QString DISPONIBILITE = ui->DISPONIBILITE->text();
                                 QString DISCRIPTION = ui->DISCRIPTION->text();
                                       QString MATIERE_PREMIERE = ui->MATIERE_PREMIERE->text();
                                            QString CATEGORIE = ui->CATEGORIE->text();

                  prod pro (ID_PRODUIT,NOM,IMAGE,DISPONIBILITE,DISCRIPTION,MATIERE_PREMIERE,CATEGORIE);



                     bool test=pro.modifier(ID_PRODUIT,NOM,IMAGE,DISPONIBILITE,DISCRIPTION,MATIERE_PREMIERE,CATEGORIE);

                     if(test)

                   {ui->tableView->setModel(pro.afficher());

                   QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                     QObject::tr("invite modifiée.\n"

                                                 "Click ok to exit."), QMessageBox::Ok);



                   }

                     else

                         QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                                     QObject::tr("echec d'ajout !.\n"

                                                 "Click Cancel to exit."), QMessageBox::Cancel);


        }




void gestion_produit::on_supprimer_clicked()
{
    prod pro;
      int ID_PRODUIT = ui->ID_PRODUIT->text().toInt();
      bool test = pro.supprimer(ID_PRODUIT);
      if (test) {
          QMessageBox::information(nullptr, QObject::tr("Ok"),
                                   QObject::tr("Suppression effectuée.\n"
                                               "Click Ok to exit."), QMessageBox::Ok);
      } else {
          QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                                QObject::tr("Échec de la suppression.\n"
                                            "Le fournisseur n'existe pas dans la base de données."),
                                QMessageBox::Cancel);
      }
      ui->tableView->setModel(pro.afficher());

}

void gestion_produit::on_afficher_clicked()
{
    prod pro;
       ui->tableView->setModel(pro.afficher());

}




void gestion_produit::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("select * from TABLE_PRODUITS where ID_PRODUIT='"+val+"'");
        if(qry.exec())
        {
         while(qry.next())
         {ui->ID_PRODUIT->setText(qry.value(0).toString());
          ui->NOM->setText(qry.value(1).toString());
          ui->IMAGE->setText(qry.value(2).toString());
          ui->DISPONIBILITE->setText(qry.value(3).toString());
          ui->DISCRIPTION->setText(qry.value(4).toString());
          ui->MATIERE_PREMIERE->setText(qry.value(5).toString());
          ui->CATEGORIE->setText(qry.value(6).toString());

         }
        }
        else
        {//qDebug()<<"Erreur  \n";
         QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        }

}
