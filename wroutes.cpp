#include "wroutes.h"
#include "ui_wroutes.h"
#include "mainwindow.h"
#include "wjournal.h"
#include "vavto.h"
#include "wautopersonal.h"
#include<QtSql/QSqlRelationalDelegate>
#include <QDebug>
#include <QMessageBox>
#include "spravka.h"
#include "info.h"
#include <QPrinter>
#include<QTextDocument>
#include<QFileDialog>
#include<QtSql/QSqlQuery>

wroutes::wroutes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wroutes)
{
    ui->setupUi(this);
}

wroutes::~wroutes()
{
    delete ui;
}

void wroutes::on_avtor_triggered()
{
    hide();
    MainWindow* window = new MainWindow(this);
       window->show();
}

void wroutes::on_journal_triggered()
{
    hide();
    wjournal* window = new wjournal(this);
       window->show();
}

void wroutes::on_avto_triggered()
{
    hide();
    vavto* window = new vavto(this);
       window->show();
}

void wroutes::on_personal_triggered()
{
    hide();
    wautopersonal* window = new wautopersonal(this);
       window->show();
}

void wroutes::on_spravka_triggered()
{

    spravka* window = new spravka(this);
       window->show();
}

void wroutes::on_info_triggered()
{
    info* window = new info(this);
       window->show();
}


void wroutes::on_routes_clicked(const QModelIndex &index)
{
    int temp_nom = ui->routes->model()->data(ui->routes->model()->index(index.row(),0)).toInt();
    ui->rid->setText(QString::number(temp_nom));

    QString temp_nom2 = ui->routes->model()->data(ui->routes->model()->index(index.row(),1)).toString();
    ui->street->setText(temp_nom2);

}

void wroutes::on_vstavkadata_clicked()
{
    rmodel = new QSqlRelationalTableModel (/*this, db*/);
    rmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    rmodel -> setEditStrategy(QSqlTableModel::OnManualSubmit);
    rmodel -> setTable("routes");
    rmodel -> select();
    ui->routes->setModel(rmodel);
    ui -> routes-> setItemDelegate(new QSqlRelationalDelegate(ui->routes));
}

void wroutes::on_addrowroutes_clicked()
{
     qDebug() << "inserting row" << rmodel -> insertRow(rmodel ->rowCount());
}

void wroutes::on_resettingcellroutes_clicked()
{
    rmodel->revertAll();
}

void wroutes::on_resettingrowroutes_clicked()
{
    rmodel ->select();
}

void wroutes::on_potvergenieroutes_clicked()
{
         rmodel -> submitAll();
}

void wroutes::on_deleteroutes_clicked()
{
    int selectedRow = ui->routes->currentIndex().row();
    if (selectedRow >=0){
        qDebug() << "deleting row:" << rmodel->removeRow(selectedRow);
    }
    else{
          QMessageBox::critical(this, "ошибка", "строки не помечены");
        qDebug() << "no row selected";
    }

}




void wroutes::on_printer_triggered()
{
    QString str;
   str.append("<html><head></head><body><center>"+QString("отчет таблица маршрутов"));
   str.append("<table border=1><tr>");
   str.append("<td>"+QString("номер")+"</td>");
   str.append("<td>"+QString("имя")+"</td></tr>");
     str.append("</td></tr>");

   QSqlQuery* query = new QSqlQuery();
   query->exec("select * from routes order by id asc");

   while(query->next())
   {
       str.append("<tr><td>");
       str.append(query->value(0).toString());
       str.append("</td><td>");
       str.append(query->value(1).toString());
       str.append("</td></tr>");



   }
   str.append("</table></center></body></html>");

   QPrinter printer;
   printer.setOrientation(QPrinter::Portrait);
   printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setPaperSize(QPrinter::A4);

   QString path = QFileDialog::getSaveFileName(NULL,"соханить в pdf", "отчет маршрутов", "PDF(*.pdf)");
   if(path.isEmpty())return;

   printer.setOutputFileName(path);

   QTextDocument doc;
   doc.setHtml(str);
   doc.print(&printer);
}
