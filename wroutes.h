#ifndef WROUTES_H
#define WROUTES_H

#include <QMainWindow>
#include <QtSql/QSqlRelationalTableModel>

namespace Ui {
class wroutes;
}

class wroutes : public QMainWindow
{
    Q_OBJECT

public:
    explicit wroutes(QWidget *parent = nullptr);
    ~wroutes();

private slots:
    void on_avtor_triggered();

    void on_journal_triggered();

    void on_avto_triggered();

    void on_personal_triggered();

    void on_routes_clicked(const QModelIndex &index);

    void on_vstavkadata_clicked();

    void on_addrowroutes_clicked();

    void on_resettingcellroutes_clicked();

    void on_resettingrowroutes_clicked();

    void on_potvergenieroutes_clicked();

    void on_deleteroutes_clicked();

    void on_spravka_triggered();

    void on_info_triggered();

    void on_printer_triggered();

private:
    Ui::wroutes *ui;
    QSqlRelationalTableModel* rmodel;
};

#endif // WROUTES_H
