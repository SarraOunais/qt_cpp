#include<iostream>
#include <QSqlError>
#include <QDebug>


#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

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
    QSqlDatabase db = QSqlDatabase::database();

    if (db.isValid()) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM employes WHERE id_employes = :id_employes");
        query.bindValue(":id_employes", id_employes);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();


            return count > 0;
        }
    }

    return false;
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



bool Employes::load(int id_employes)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE id_employes = :id");
    query.bindValue(":id", id_employes);

    if (query.exec() && query.first()) {
        // Remplir les attributs de la classe avec les données de la base de données
        this->id_employes = query.value("employes_id").toInt();
        this->nom = query.value("nom").toString();
        this->prenom = query.value("prenom").toString();
        this->email = query.value("email").toString();
        this->role = query.value("role").toString();
        this->sexe = query.value("sexe").toString();
        this->mot_de_passe = query.value("mot_de_passe").toString();
        this->CIN = query.value("CIN").toDouble();
        this->RIB = query.value("RIB").toDouble();
        this->date_naissance = query.value("date_naissance").toDate();
        this->date_embauche = query.value("date_embauche").toDate();
        this->salaire = query.value("salaire").toDouble();
        // Continuez avec d'autres attributs au besoin
        // ...

        return true;
    }

    return false;
}


QSqlQueryModel *Employes::rechercher_nom(const QString &nom)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM employes WHERE nom = :nom");
    query.bindValue(":nom", nom);

    if (query.exec())
    {
        model->setQuery(query);
        return model;
    }
    else
    {
        qDebug() << "Recherche par marque échouée : " << query.lastError();
        delete model;
        return nullptr;
    }
}


QSqlQueryModel *Employes::trier_dateEmbauche()
{
    QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery("SELECT * FROM employes ORDER BY date_embauche ASC");
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



QList<Employes> Employes::getAllEmployees()
{
    QList<Employes> employees;


        QSqlQuery query("SELECT * FROM employes");

        while (query.next()) {
            int id_employes = query.value("id_employes").toInt();
            QString nom = query.value("nom").toString();
            QString prenom = query.value("prenom").toString();
            QString email = query.value("email").toString();
            QString sexe = query.value("sexe").toString();
            QString role = query.value("role").toString();
            QString mot_de_passe = query.value("mot_de_passe").toString();
            int CIN = query.value("CIN").toInt();
            int RIB = query.value("RIB").toInt();
            QDate date_embauche = query.value("date_embauche").toDate();
            QDate date_naissance = query.value("date_naissance").toDate();
            float salaire = query.value("salaire").toFloat();



            Employes e(nom, prenom, email, role, sexe, mot_de_passe, id_employes, CIN, RIB, date_naissance, date_embauche, salaire);
            employees.append(e);
        }


    return employees;
}



QT_CHARTS_USE_NAMESPACE


QChartView* Employes::statistique()
{
    QSqlQuery query;
    int totalEmployees = 0;
    int maleCount = 0;
    int femaleCount = 0;
    double pourc_homme,pourc_femme;


    if (query.exec("SELECT COUNT(*) FROM employes")) {
        if (query.next()) {
            totalEmployees = query.value(0).toInt();
        }
    }

    if (query.exec("SELECT COUNT(*) FROM employes WHERE sexe = 'Homme'")) {
        if (query.next()) {
            maleCount = query.value(0).toInt();
        }
    }

    if (query.exec("SELECT COUNT(*) FROM employes WHERE sexe = 'Femme'")) {
        if (query.next()) {
            femaleCount = query.value(0).toInt();
        }
    }

    pourc_homme = (static_cast<double>(maleCount) / totalEmployees) * 100;
    pourc_femme = (static_cast<double>(femaleCount) / totalEmployees) * 100;

    QPieSeries *series = new QPieSeries();
    QPieSlice *sliceJane = new QPieSlice("FEMME", pourc_femme);
    QPieSlice *sliceHomme = new QPieSlice("HOMME", pourc_homme);

    sliceJane->setBrush(QColor("#F849F1"));
    sliceJane->setPen(QPen(QColor("#F849F1"), 2));
    sliceHomme->setBrush(QColor("#1EC8DF"));
    sliceHomme->setPen(QPen(QColor("#1EC8DF"), 2));

    series->append(sliceJane);
    series->append(sliceHomme);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique Hommes/Femme");


    double total = 0;
    for (QPieSlice *slice : series->slices()) {
        total += slice->value();
    }


    for (QPieSlice *slice : series->slices()) {
        slice->setExploded();
        slice->setLabelVisible();


        double percentage = (slice->value() / total) * 100;
        QString label = QString("%1 (%2%)").arg(slice->label()).arg(percentage, 0, 'f', 1);
        slice->setLabel(label);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}



