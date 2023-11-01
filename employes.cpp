#include<iostream>
#include <QSqlError>
#include <QDebug>
#include "employes.h"

Employes::Employes(QString nom, QString prenom, QString email, QString role, QString sexe, QString mot_de_passe, int id_employes, double CIN, double RIB, QDate date_naissance, QDate date_embauche, float salaire)
{
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->role = role;
    this->sexe = sexe;
    this->mot_de_passe = mot_de_passe;
    this->id_employes = id_employes;
    this->CIN = CIN;
    this->RIB = RIB;
    this->date_naissance = date_naissance;
    this->date_embauche = date_embauche;
    this->salaire = salaire;

}
Employes::Employes(int id)
{
    id_employes = id;
}

bool Employes::ajouter()
{
    QSqlQuery query;
    QString ch_id=QString::number(id_employes);
    QString ch_CIN=QString::number(CIN);
    QString ch_RIB=QString::number(RIB);
    QString ch_salaire=QString::number(salaire);
    query.prepare("insert into employes (nom,prenom,email,role,sexe,mot_de_passe,id_employes,CIN,RIB,date_naissance,date_embauche,salaire) values(:nom,:prenom,:email,:role,:sexe,:mot_de_passe,:id_employes,:CIN,:RIB,:date_naissance,:date_embauche,:salaire)");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":role",role);
    query.bindValue(":sexe",sexe);
    query.bindValue(":mot_de_passe",mot_de_passe);
    query.bindValue(":id_employes",ch_id);
    query.bindValue(":CIN",ch_CIN);
    query.bindValue(":RIB",ch_RIB);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":date_embauche",date_embauche);
    query.bindValue(":salaire",ch_salaire);
    return query.exec();
}


QSqlQueryModel * Employes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from employes");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_employes"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("role"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("mot_de_passe"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("RIB"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("date_naissance"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("date_embauche"));

    return model;
}

bool Employes::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE FROM employes WHERE ID_EMPLOYES = :id");
    query.bindValue(":id", res);

    if (query.exec())
    {
        if (query.numRowsAffected() > 0)
            return true;
    }
    return false;
}



bool Employes::existe()
{
    QSqlDatabase db = QSqlDatabase::database(); // Assurez-vous que la connexion à la base de données est établie.

    if (db.isValid()) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM employes WHERE id_employes = :id_employes");
        query.bindValue(":id_employes", id_employes);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();

            // Si count est supérieur à zéro, cela signifie que l'employé existe dans la base de données.
            return count > 0;
        }
    }

    return false; // En cas d'erreur ou si l'employé n'existe pas.
}




bool Employes::modifier()
{
    QSqlQuery query;
    QString ch_id = QString::number(id_employes);
    QString ch_CIN = QString::number(CIN);
    QString ch_RIB = QString::number(RIB);
    QString ch_salaire = QString::number(salaire);
    query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, email = :email, role = :role, sexe = :sexe, mot_de_passe = :mot_de_passe, CIN = :CIN, RIB = :RIB, date_naissance = :date_naissance, date_embauche = :date_embauche, salaire = :salaire WHERE id_employes = :id_employes");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":role", role);
    query.bindValue(":sexe", sexe);
    query.bindValue(":mot_de_passe", mot_de_passe);
    query.bindValue(":id_employes", id_employes);
    query.bindValue(":CIN", ch_CIN);
    query.bindValue(":RIB", ch_RIB);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":date_embauche", date_embauche);
    query.bindValue(":salaire", ch_salaire);
    return query.exec();
}







/*
bool Employes::modifier()
{
    QSqlQuery query;
        query.prepare("UPDATE employes SET nom = :nom, prenom = :prenom, email = :email, role = :role, mot_de_passe = :mot_de_passe, CIN = :CIN, RIB = :RIB, salaire = :salaire, date_naissance = :date_naissance, date_embauche = :date_embauche, sexe = :sexe WHERE id_employes = :id_employes");
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":email", email);
        query.bindValue(":role", role);
        query.bindValue(":mot_de_passe", mot_de_passe);
        query.bindValue(":CIN", CIN);
        query.bindValue(":RIB", RIB);
        query.bindValue(":salaire", salaire);
        query.bindValue(":date_naissance", date_naissance);
        query.bindValue(":date_embauche", date_embauche);
        query.bindValue(":sexe", sexe);
        query.bindValue(":id_employes", id_employes);
        return query.exec();
}*/

/*
bool Employes::modifier()
{
    QSqlQuery query;
    QString ch_id = QString::number(id_employes);
    QString ch_CIN=QString::number(CIN);
    QString ch_RIB=QString::number(RIB);
    QString ch_salaire=QString::number(salaire);
    query.bindValue(":employes_id", ch_id);

    // Conditionnellement, liez les valeurs pour les attributs non vides.
    if (!nom.isEmpty()) {
        query.prepare("UPDATE employes SET nom = :nom WHERE id_employes = :id_employes");
        query.bindValue(":nom", nom);
        std::cout<<"nom not empty";
    }
    if (!prenom.isEmpty()) {
        query.prepare("UPDATE employes SET prenom = :prenom WHERE id_employes = :id_employes");
        query.bindValue(":prenom", prenom);
    }
    if (!email.isEmpty()) {
        query.prepare("UPDATE employes SET Email = :email WHERE id_employes = :id_employes");
        query.bindValue(":email", email);
    }
    if (!role.isEmpty()) {
        query.prepare("UPDATE employes SET role = :role WHERE id_employes = :id_employes");
        query.bindValue(":role", role);
    }
    if (!sexe.isEmpty()) {
        query.prepare("UPDATE employes SET sexe = :sexe WHERE id_employes = :id_employes");
        query.bindValue(":sexe", sexe);
    }
    if (!mot_de_passe.isEmpty()) {
        query.prepare("UPDATE employes SET mot_de_passe = :mot_de_passe WHERE id_employes = :id_employes");
        query.bindValue(":mot_de_passe", mot_de_passe);
    }
    if (!ch_CIN.isEmpty()) {
        query.prepare("UPDATE employes SET CIN = :cin WHERE id_employes = :id_employes");
        query.bindValue(":cin", ch_CIN);
    }
    if (!ch_RIB.isEmpty()) {
        query.prepare("UPDATE employes SET RIB = :rib WHERE id_employes = :id_employes");
        query.bindValue(":rib", ch_RIB);
    }
    if (date_naissance.isValid()) {
        query.prepare("UPDATE employes SET date_naissance = :date_naissance WHERE id_employes = :id_employes");
        query.bindValue(":date_naissance", date_naissance);
    }
    if (date_embauche.isValid()) {
        query.prepare("UPDATE employes SET date_embauche = :date_embauche WHERE id_employes = :id_employes");
        query.bindValue(":date_embauche", date_embauche);
    }
    if (!ch_salaire.isEmpty()) {
        query.prepare("UPDATE employes SET salaire = :salaire WHERE id_employes = :id_employes");
        query.bindValue(":salaire", ch_salaire);
    }

    // Assurez-vous que ch_id correspond à l'employes_id de l'employé que vous souhaitez modifier.

    if (query.exec()) {
        return true; // La mise à jour a réussi.
    } else {
        QSqlError error = query.lastError();
            qDebug() << "Erreur SQL : " << error.text();
            qDebug() << "Numéro de l'erreur : " << error.number();
            qDebug() << "Type de l'erreur : " << error.type();
        return false; // La mise à jour a échoué.
    }

}*/

