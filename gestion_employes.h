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

    void on_pred_p0_clicked();

    void on_boutton_modifier_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_chercher_nom_clicked();

    void on_refresh_clicked();

    void on_button_trier_clicked();

    void on_button_genererPDF_clicked();

    QString getEmployeeField(const Employes &employee, int columnIndex);

    void on_button_statistique_clicked();

    void addTask(const QDate &date, const QString &taskText);

    void on_boutton_ajouter_tache_clicked();

    void updateListViewForDate(const QDate &selectedDate);

    void on_calendarWidget_selectionChanged();

    void on_boutton_valider_clicked();

private:
    Ui::gestion_employes *ui;
    QDate selectedDate;
    QMap<QDate, QStringList> tasksByDate;

};
#endif // GESTION_EMPLOYES_H
