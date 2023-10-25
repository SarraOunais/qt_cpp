#include "employes.h"

Employes::Employes(QString nom, QString prenom, QString email, QString role, QString sexe, QString mot_de_passe, int id_employes, int CIN, int RIB, QDate date_naissance, QDate date_embauche, float salaire)
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

