#ifndef WAUTOPERSONAL_H
#define WAUTOPERSONAL_H

#include <QMainWindow>
#include <QtSql/QSqlRelationalTableModel>

namespace Ui {
class wautopersonal;
}

class wautopersonal : public QMainWindow
{
    Q_OBJECT

public:
    explicit wautopersonal(QWidget *parent = nullptr);
    ~wautopersonal();

private slots:
    void on_avtor_triggered();

    void on_journal_triggered();


    void on_avto_triggered();

    void on_vstavkadata_clicked();

    void on_personal_clicked(const QModelIndex &index);

    void on_addrowpersonal_clicked();

    void on_resettingcellpersonal_clicked();

    void on_resettingrowpersonal_clicked();

    void on_potvergeniepersonal_clicked();

    void on_deletepersonal_clicked();

    void on_routes_triggered();

    void on_spravka_triggered();

    void on_info_triggered();

    void on_printer_triggered();

private:
    Ui::wautopersonal *ui;
    QSqlRelationalTableModel* apmodel;
};

#endif // WAUTOPERSONAL_H
