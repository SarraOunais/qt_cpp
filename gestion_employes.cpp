#include<QString>
#include <QMessageBox>

#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextTable>
#include <QTextCursor>
#include <QTextTableCell>
#include <QTextFrame>
#include <QTextBlock>
#include <QTextCharFormat>

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

#include <QPdfWriter>
#include <QFileDialog>
#include <QPageSize>

#include <QDebug>


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
             return;
        }

    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || role.isEmpty() || mot_de_passe.isEmpty() || ui->id_e->text().isEmpty() || ui->CIN_e->text().isEmpty() || ui->RIB_e->text().isEmpty() || ui->salaire_e->text().isEmpty() ) {
            QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
            return;
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




void gestion_employes::on_tableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row(); // Récupérer la ligne sélectionnée dans le tableau

        // Utilisez le modèle de données pour accéder aux informations de l'employé
        QModelIndex idIndex = ui->tableView->model()->index(row, 0); // Supposons que la colonne 0 contient l'ID de l'employé
        int id_employes = ui->tableView->model()->data(idIndex).toInt();

        Employes E;

        // Charger les données de l'employé à partir de la base de données
        if (E.load(id_employes)) {
            // Remplir les labels avec les attributs de l'employé
            ui->nom_e->setText(E.getNom());
            ui->prenom_e->setText(E.getPrenom());
            ui->email_e->setText(E.getEmail());
            ui->mdp_e->setText(E.getMotDePasse());
            ui->CIN_e->setText(QString::number(E.getCIN()));
            ui->RIB_e->setText(QString::number(E.getRIB()));
            ui->date_naissance->setDate(E.getDate_naissance());
            ui->date_embauche->setDate(E.getDate_embauche());
            ui->salaire_e->setText(QString::number(E.getSalaire()));
            ui->id_e->setText(QString::number(id_employes));
            ui->role_e->setText(E.getRole());
            if (E.getSexe() == "Homme") {
                        ui->homme->setChecked(true);
                        ui->femme->setChecked(false);
                    } else if (E.getSexe() == "Femme") {
                        ui->homme->setChecked(false);
                        ui->femme->setChecked(true);
                    }

            // Continuez avec d'autres labels pour les attributs restants

            // Assurez-vous de gérer les labels pour les attributs restants de la même manière
        } else {
            // Gérer l'erreur si l'employé n'est pas trouvé
            QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'a pas été trouvé."), QMessageBox::Ok);
        }
}



void gestion_employes::on_chercher_nom_clicked()
{
    Employes e;
    QString chercher_nom = ui->recherche_nom->text();

        QSqlQueryModel *results = e.rechercher_nom(chercher_nom );

        if (results)
        {
            ui->tableView->setModel(results);
            ui->tableView->resizeColumnsToContents();
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "La recherche a échoué. Veuillez réessayer.");
        }
}

void gestion_employes::on_refresh_clicked()
{
    Employes e;
    ui->tableView->setModel(e.afficher());
    ui->tableView->resizeColumnsToContents();
    ui->recherche_nom->clear();
}

void gestion_employes::on_button_trier_clicked()
{
    Employes e;
    QSqlQueryModel *Model = e.trier_dateEmbauche();
    ui->tableView->setModel(Model);
}




void gestion_employes::on_button_genererPDF_clicked()
{
    Employes e;
    QList<Employes> employees = e.getAllEmployees();
    if (employees.isEmpty()) {
        // Gérer le cas où aucun employé n'est trouvé dans la base de données
        return;
    }

    QFileDialog dialog(this);
    QString filePath = dialog.getSaveFileName(this, "Enregistrer le fichier PDF", "C:/Users/ounai/Desktop/Gestion_employes_projet++/employees.pdf", "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter(&pdfWriter);

    // Définir la mise en page du document PDF et les polices
    QFont font;
    font.setPixelSize(100); // Ajuster la taille de la police à 100 pixels
    painter.setFont(font);

    int y = 20; // Position verticale initiale

    // Définir les largeurs des colonnes et leurs étiquettes
    const int colWidth = 800;
    const QStringList colLabels = {"ID", "Nom", "Prénom", "Email", "Sexe", "Rôle", "mot de passe", "CIN", "RIB", "Salaire", "Naissance", "Embauche"};

    // Dessiner la première ligne avec les étiquettes de colonnes
    for (int i = 0; i < colLabels.size(); i++) {
        painter.drawText(i * colWidth, y, colWidth, 100, Qt::AlignLeft, colLabels[i]);
    }
    y += 200; // Déplacement vertical pour les données

    for (const Employes &employee : employees) {
        // Dessiner une ligne pour chaque employé
        for (int i = 0; i < colLabels.size(); i++) {
            painter.drawText(i * colWidth, y, colWidth, 100, Qt::AlignLeft, getEmployeeField(employee, i));
        }
        y += 200; // Déplacement vertical pour la prochaine ligne
    }

    bool exportSuccess = painter.end();
    if (exportSuccess) {
        QMessageBox::information(this, "Success", "Les informations des employés ont été exportées vers le fichier PDF.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'exportation des informations des employés vers le fichier PDF.");
    }
}


QString gestion_employes::getEmployeeField(const Employes &employee, int columnIndex)
{
    switch (columnIndex) {
        case 0: return QString::number(employee.getIdEmployes());
        case 1: return employee.getNom();
        case 2: return employee.getPrenom();
        case 3: return employee.getEmail();
        case 4: return employee.getSexe();
        case 5: return employee.getRole();
        case 6: return employee.getMotDePasse();
        case 7: return QString::number(employee.getCIN());
        case 8: return QString::number(employee.getRIB());
        case 9: return QString::number(employee.getSalaire());
        case 10: return employee.getDate_naissance().toString("yyyy-MM-dd");
        case 11: return employee.getDate_embauche().toString("yyyy-MM-dd");


        default: return QString();
    }


}

