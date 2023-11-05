#ifndef GESTION_PRODUIT_H
#define GESTION_PRODUIT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class gestion_produit; }
QT_END_NAMESPACE

class gestion_produit : public QMainWindow
{
    Q_OBJECT

public:
    gestion_produit(QWidget *parent = nullptr);
    ~gestion_produit();

private slots:
    void on_ajouter_clicked();
    void on_afficher_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::gestion_produit *ui;
};
#endif // GESTION_PRODUIT_H
