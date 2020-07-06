#ifndef VAVTO_H
#define VAVTO_H

#include <QMainWindow>
#include <QtSql/QSqlRelationalTableModel>

namespace Ui {
class vavto;
}

class vavto : public QMainWindow
{
    Q_OBJECT

public:
    explicit vavto(QWidget *parent = nullptr);
    ~vavto();

private slots:
    void on_avtor_triggered();

    void on_wjournal_triggered();

    void on_vstavkadata_clicked();

    void on_auto_2_clicked(const QModelIndex &index);

    void on_addrowauto_clicked();

    void on_resettingcellauto_clicked();

    void on_resettingrowauto_clicked();

    void on_potvergenieauto_clicked();

    void on_deleteauto_clicked();

    void on_personal_triggered();



    void on_routes_triggered();

    void on_spravka_triggered();

    void on_info_triggered();

    void on_printer_triggered();

private:
    Ui::vavto *ui;
      QSqlRelationalTableModel* amodel;
};

#endif // VAVTO_H
