#ifndef GESTION_EMPLOYES_H
#define GESTION_EMPLOYES_H

#include <QMainWindow>
#include "employes.h"
QT_BEGIN_NAMESPACE
namespace Ui { class gestion_employes; }
QT_END_NAMESPACE

class gestion_employes : public QMainWindow
{

    Q_OBJECT

public:
     gestion_employes(QWidget *parent = nullptr);

    ~gestion_employes();

private slots:
    void on_boutton_ajouter_clicked();
    QString getSelectedGender();

    void on_next_p1_clicked();

    void on_boutton_supprimer_clicked();

    void on_next_p2_clicked();

    void on_pred_p1_clicked();

    void on_pred_p0_clicked();

    void on_boutton_modifier_clicked();

private:
    Ui::gestion_employes *ui;

};
#endif // GESTION_EMPLOYES_H
