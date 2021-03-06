#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_avtor_2_clicked();

    void on_spravka_triggered();

    void on_info_triggered();

private:
    Ui::MainWindow *ui;
       QSqlDatabase db;
};
#endif // MAINWINDOW_H
