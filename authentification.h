#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QDialog>
#include "gestion_employes.h"
namespace Ui {
class Authentification;
}

class Authentification : public QDialog
{
    Q_OBJECT

public:
    explicit Authentification(QWidget *parent = nullptr);
    ~Authentification();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Authentification *ui;
    bool authenticateEmployee(int id_employes, const QString &password);
    gestion_employes w;
};

#endif // AUTHENTIFICATION_H
