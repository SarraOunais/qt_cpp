#include <QMessageBox>
#include <QSqlQuery>
#include "employes.h"
#include "gestion_employes.h"
#include "authentification.h"
#include "ui_authentification.h"

Authentification::Authentification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authentification)
{
    ui->setupUi(this);
}


Authentification::~Authentification()
{
    delete ui;
}


bool Authentification::authenticateEmployee(int id_employes, const QString &password)
{

    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE id_employes = :id_employes AND mot_de_passe = :password");
    query.bindValue(":id_employes", id_employes);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {

        return true;
    } else {

        return false;
    }
}

void Authentification::on_pushButton_clicked()//login_button
{
    int id = ui->id_employe->text().toInt();
    QString password = ui->mdp_employe->text();

            if (authenticateEmployee(id, password)) {
                w.show();
                this->hide();
            } else {
                QMessageBox::critical(this, "Login Error", "Invalid ID or password.");
            }


}
