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
    ui->tableView->resizeColumnsToContents();
    ui->CIN_e->setValidator(new QIntValidator(0,99999999,this));

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
    int id_employes=ui->id_e->text().toDouble();
    double CIN=ui->CIN_e->text().toDouble();
    double RIB=ui->RIB_e->text().toDouble();
    float salaire=ui->salaire_e->text().toFloat();
    QDate date_naissance=ui->date_naissance->date();
    QDate date_embauche=ui->date_embauche->date();
    QString sexe=getSelectedGender();

    QRegExp regex("^[a-zA-Z0-9]+$");  // Mot de passe composé de lettres et de chiffres seulement

    if (!regex.exactMatch(mot_de_passe))
        {
             QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Mot de passe non valide. Utilisez uniquement des lettres et des chiffres."), QMessageBox::Cancel);
             return;
        }
             QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

    if (!emailRegex.exactMatch(email)) {
             QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Adresse email non valide. Utilisez le format abc@abc.abc."), QMessageBox::Cancel);
             return;  // Sortez de la fonction si la vérification échoue
        }

    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || role.isEmpty() || mot_de_passe.isEmpty() || ui->id_e->text().isEmpty() || ui->CIN_e->text().isEmpty() || ui->RIB_e->text().isEmpty() || ui->salaire_e->text().isEmpty() ) {
            QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
            return; // Arrêtez l'exécution si les données sont invalides.
        }

        if (salaire <= 0.0) {
            QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le salaire doit être supérieur à zéro."));
            return;
        }

        if (date_naissance > date_embauche) {
            QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("La date de naissance ne peut pas être postérieure à la date d'embauche."));
            return;
        }
    Employes e(nom,prenom,email,role,sexe,mot_de_passe,id_employes,CIN,RIB,date_naissance,date_embauche,salaire);
    bool test=e.ajouter();
    if(test)
    {
        ui->tableView->setModel(e1.afficher());
        ui->tableView->resizeColumnsToContents();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->nom_e->clear();
        ui->prenom_e->clear();
        ui->email_e->clear();
        ui->role_e->clear();
        ui->mdp_e->clear();
        ui->id_e->clear();
        ui->CIN_e->clear();
        ui->RIB_e->clear();
        ui->salaire_e->clear();
        ui->date_naissance->setDate(QDate::currentDate());
        ui->date_embauche->setDate(QDate::currentDate());


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


void gestion_employes::on_next_p2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void gestion_employes::on_pred_p1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void gestion_employes::on_pred_p0_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



void gestion_employes::on_boutton_supprimer_clicked()
{
    Employes e;
    int id=ui->id_e_supp->text().toInt();
    e.setIdEmployes(id);
    if (e.existe()) {
        bool test=e.supprimer(id);
        if(test)
        {
            ui->tableView->setModel(e.afficher());
            ui->tableView->resizeColumnsToContents();
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("suppression effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                        QObject::tr("supression non effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("L'employé n'existe pas. Supression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void gestion_employes::on_boutton_modifier_clicked()
{
    Employes e1;
    QString nom = ui->nom_e->text();
    QString prenom = ui->prenom_e->text();
    QString email = ui->email_e->text();
    QString role = ui->role_e->text();
    QString mot_de_passe = ui->mdp_e->text();
    int id_employes=ui->id_e->text().toDouble();
    double CIN=ui->CIN_e->text().toDouble();
    double RIB=ui->RIB_e->text().toDouble();
    float salaire = ui->salaire_e->text().toFloat();
    QDate date_naissance = ui->date_naissance->date();
    QDate date_embauche = ui->date_embauche->date();
    QString sexe = getSelectedGender();


    if (salaire <= 0.0) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le salaire doit être supérieur à zéro."));
        return;
    }

    if (date_naissance > date_embauche) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("La date de naissance ne peut pas être postérieure à la date d'embauche."));
        return;
    }

    Employes e(nom, prenom, email, role, sexe, mot_de_passe, id_employes, CIN, RIB, date_naissance, date_embauche, salaire);
    if (e.existe()) {
        bool test = e.modifier();

        if (test)
        {
            ui->tableView->setModel(e1.afficher());
            ui->tableView->resizeColumnsToContents();
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Modification effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->nom_e->clear();
            ui->prenom_e->clear();
            ui->email_e->clear();
            ui->role_e->clear();
            ui->mdp_e->clear();
            ui->id_e->clear();
            ui->CIN_e->clear();
            ui->RIB_e->clear();
            ui->salaire_e->clear();
            ui->date_naissance->setDate(QDate::currentDate());
            ui->date_embauche->setDate(QDate::currentDate());
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                        QObject::tr("Modification non effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("L'employé n'existe pas. Modification non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


/*
void gestion_employes::on_boutton_modifier_clicked()
{

        Employes e1;
        QString nom = ui->nom_e->text();
        QString prenom = ui->prenom_e->text();
        QString email = ui->email_e->text();
        QString role = ui->role_e->text();
        QString mot_de_passe = ui->mdp_e->text();
        int id_employes = ui->id_e->text().toInt();
        int CIN = ui->CIN_e->text().toInt();
        int RIB = ui->RIB_e->text().toInt();
        float salaire = ui->salaire_e->text().toFloat();
        QDate date_naissance = ui->date_naissance->date();
        QDate date_embauche = ui->date_embauche->date();
        QString sexe = getSelectedGender();

        // Vérifiez quelles valeurs sont vides et les récupérer uniquement s'ils ne sont pas vides.
        Employes e(id_employes); // Vous pouvez créer un constructeur dans la classe Employes qui prend l'ID pour obtenir les données existantes.
        if (!nom.isEmpty()) e.setNom(nom);
        if (!prenom.isEmpty()) e.setPrenom(prenom);
        if (!email.isEmpty()) e.setEmail(email);
        if (!role.isEmpty()) e.setRole(role);
        if (!mot_de_passe.isEmpty()) e.setMotDePasse(mot_de_passe);
        if (CIN != 0) e.setCIN(CIN);
        if (RIB != 0) e.setRIB(RIB);
        if (salaire != 0) e.setSalaire(salaire);
        if (date_naissance.isValid()) e.setDate_naissance(date_naissance);
        if (date_embauche.isValid()) e.setDate_embauche(date_embauche);
        if (!sexe.isEmpty()) e.setSexe(sexe);

        bool test = e.modifier(); // Ajoutez une fonction "modifier" à la classe Employes pour effectuer la mise à jour.
        if (test)
        {
            ui->tableView->setModel(e1.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Modification effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                        QObject::tr("Modification non effectuée.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


}
*/

/*
void gestion_employes::on_boutton_modifier_clicked()
{
    Employes e1;
    QString nom = ui->nom_e->text();
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

           // Créez un objet Employes avec les données
           Employes e(nom,prenom,email,role,sexe,mot_de_passe,id_employes,CIN,RIB,date_naissance,date_embauche,salaire);

           // Vérifiez d'abord si l'employé existe
           if (e.existe()) {
               // Si l'employé existe, appelez la fonction "modifier" pour mettre à jour
               bool test = e.modifier();
               if (test) {
                   ui->tableView->setModel(e1.afficher());
                   QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Modification effectuée. Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);
               } else {
                   QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Modification non effectuée. Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);
               }
           } else {
               QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'existe pas. Modification non effectuée. Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);
           }

}
*/
