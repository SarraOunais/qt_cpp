#include<QString>
#include <QMessageBox>
#include "gestion_employes.h"
#include "ui_gestion_employes.h"
#include "employes.h"

gestion_employes::gestion_employes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_employes)
{
    Employes e;
    ui->setupUi(this);
    ui->tableView->setModel(e.afficher());
}

gestion_employes::~gestion_employes()
{
    delete ui;
}

QString gestion_employes::getSelectedGender() {
    QButtonGroup genderButtonGroup;
    genderButtonGroup.addButton(ui->homme);
    genderButtonGroup.addButton(ui->femme);
    QAbstractButton* selectedButton = genderButtonGroup.checkedButton();

    if (selectedButton == ui->homme) {
        return "Homme";
    } else if (selectedButton == ui->femme) {
        return "Femme";
    } else {
        return "Non spécifié";
    }
}



void gestion_employes::on_boutton_ajouter_clicked()
{
    Employes e1;
    QString nom=ui->nom_e->text();
    QString prenom=ui->prenom_e->text();
    QString email=ui->email_e->text();
    QString role=ui->role_e->text();
    QString mot_de_passe=ui->mdp_e->text();
    int id_employes=ui->id_e->text().toInt();
    int CIN=ui->CIN_e->text().toInt();
    int RIB=ui->RIB_e->text().toInt();
    float salaire=ui->salaire_e->text().toFloat();
    QDate date_naissance=ui->date_naissance->date();
    QDate date_embauche=ui->date_embauche->date();
    QString sexe=getSelectedGender();
    Employes e(nom,prenom,email,role,sexe,mot_de_passe,id_employes,CIN,RIB,date_naissance,date_embauche,salaire);
    bool test=e.ajouter();
    if(test)
    {
        ui->tableView->setModel(e1.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}




void gestion_employes::on_next_p1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



