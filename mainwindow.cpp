#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include"wjournal.h"
#include"spravka.h"
#include"info.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_avtor_2_clicked()
{
    db = QSqlDatabase:: addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName(""+ui->baza->text());
    db.setUserName(""+ui->login->text());
    db.setPassword(""+ui->parol->text());
    if (!db.open()){
         QMessageBox::critical(this, "ошибка", "введите праильно пользоатель и пароль");
      }
    else {
        hide();
       qDebug() << "Success!";
       wjournal* window = new wjournal(this);
          window->show();
    }
}


void MainWindow::on_spravka_triggered()
{
    spravka* window = new spravka(this);
       window->show();
}

void MainWindow::on_info_triggered()
{
    info* window = new info(this);
       window->show();
}
