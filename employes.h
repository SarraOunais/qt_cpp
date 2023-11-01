#ifndef EMPLOYES_H
#define EMPLOYES_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>

class Employes
{
  QString nom,prenom,email,role,sexe,mot_de_passe;
  int id_employes;
  double  CIN,RIB;
  QDate date_naissance,date_embauche;
  float salaire;
public:

    Employes(){};
    Employes(QString,QString,QString,QString,QString,QString,int,double,double,QDate,QDate,float);
    Employes(int id);

    //Getters
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getEmail(){return email;}
    QString getRole(){return role;}
    QString getSexe(){return sexe;}
    QString getMotDePasse(){return mot_de_passe;}
    int getIdEmployes(){return id_employes;}
    double getCIN(){return CIN;}
    double getRIB(){return RIB;}
    QDate getDate_naissance(){return date_naissance;};
    QDate getDate_embauche(){return date_embauche;};
    float getSalaire(){return salaire;};

    //Setters
    void setNom(const QString &nouveauNom) { nom = nouveauNom; }
    void setPrenom(const QString &nouveauPrenom) { prenom = nouveauPrenom; }
    void setEmail(const QString &nouvelEmail) { email = nouvelEmail; }
    void setRole(const QString &nouveauRole) { role = nouveauRole; }
    void setSexe(const QString &nouveauSexe) { sexe = nouveauSexe; }
    void setMotDePasse(const QString &nouveauMotDePasse) { mot_de_passe = nouveauMotDePasse; }
    void setIdEmployes(int nouvelIdEmployes) { id_employes = nouvelIdEmployes; }
    void setCIN(double nouveauCIN) { CIN = nouveauCIN; }
    void setRIB(double nouveauRIB) { RIB = nouveauRIB; }
    void setDate_naissance(const QDate &nouvelleDateNaissance) { date_naissance = nouvelleDateNaissance; }
    void setDate_embauche(const QDate &nouvelleDateEmbauche) { date_embauche = nouvelleDateEmbauche; }
    void setSalaire(float nouveauSalaire) { salaire = nouveauSalaire; }

    //methodes
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    bool existe();
};

#endif // EMPLOYES_H
