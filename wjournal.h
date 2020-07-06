#ifndef WJOURNAL_H
#define WJOURNAL_H

#include <QMainWindow>
#include <QtSql/QSqlRelationalTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class wjournal;
}
QT_END_NAMESPACE

class wjournal : public QMainWindow
{
    Q_OBJECT

public:
    explicit wjournal(QWidget *parent = nullptr);
    ~wjournal();

private slots:


    void on_vstavkadata_clicked();

    void on_journal_clicked(const QModelIndex &index);

    void on_addrowjournal_clicked();

    void on_resettingcelljournal_clicked();

    void on_resettingrowjournal_clicked();

    void on_potvergeniejournal_clicked();

    void on_deletejournal_clicked();


    void on_avtor_triggered();

    void on_avto_triggered();

    void on_personal_triggered();

    void on_routes_triggered();

    void on_spravka_triggered();

    void on_info_triggered();


    void on_printer_triggered();

private:
    Ui::wjournal *ui;

      QSqlRelationalTableModel* jmodel;
};

#endif // WJOURNAL_H
