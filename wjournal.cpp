#include "wjournal.h"
#include "ui_wjournal.h"
#include "mainwindow.h"
#include<QtSql/QSqlRelationalDelegate>
#include <QDebug>
#include <QMessageBox>
#include "vavto.h"
#include "wautopersonal.h"
#include "wroutes.h"
#include "spravka.h"
#include "info.h"
#include <QPrinter>
#include<QTextDocument>
#include<QFileDialog>
#include<QtSql/QSqlQuery>


wjournal::wjournal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wjournal)
{
    ui->setupUi(this);
}

wjournal::~wjournal()
{
    delete ui;
}

void wjournal::on_avtor_triggered()
{
    hide();
    MainWindow* window = new MainWindow(this);
       window->show();
}


void wjournal::on_avto_triggered()
{
    hide();
    vavto* window = new vavto(this);
       window->show();
}

void wjournal::on_personal_triggered()
{
    hide();
    wautopersonal* window = new wautopersonal(this);
       window->show();
}


void wjournal::on_routes_triggered()
{
    hide();
    wroutes* window = new wroutes(this);
       window->show();
}
void wjournal::on_spravka_triggered()
{
    spravka* window = new spravka(this);
       window->show();
}

void wjournal::on_info_triggered()
{
    info* window = new info(this);
       window->show();
}

void wjournal::on_vstavkadata_clicked()
{
    jmodel  = new QSqlRelationalTableModel ();
    jmodel ->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    jmodel -> setEditStrategy(QSqlTableModel::OnManualSubmit);

    jmodel -> setTable("journal");
    jmodel -> setRelation(jmodel->fieldIndex("routes_id"),
                          QSqlRelation("routes","id", "name"));
    jmodel -> setRelation(jmodel->fieldIndex("auto_id"),
                          QSqlRelation("auto","id", "num"));
    jmodel -> select();
    ui->journal->setModel(jmodel);
    ui -> journal-> setItemDelegate(new QSqlRelationalDelegate(ui->journal));

}

void wjournal::on_journal_clicked(const QModelIndex &index)
{
    int temp_nom = ui->journal->model()->data(ui->journal->model()->index(index.row(),0)).toInt();
    ui->jid->setText(QString::number(temp_nom));

    QString temp_nom2 = ui->journal->model()->data(ui->journal->model()->index(index.row(),1)).toString();
    ui->time_out->setText(temp_nom2);

    QString temp_nom3 = ui->journal->model()->data(ui->journal->model()->index(index.row(),2)).toString();
    ui->time_in->setText(temp_nom3);

    QString temp_nom4 = ui->journal->model()->data(ui->journal->model()->index(index.row(),3)).toString();
    ui->routes_id->setText(temp_nom4);

    QString temp_nom5 = ui->journal->model()->data(ui->journal->model()->index(index.row(),4)).toString();
    ui->auto_id->setText(temp_nom5);
}

void wjournal::on_addrowjournal_clicked()
{

    qDebug() << "inserting row" << jmodel -> insertRow(jmodel ->rowCount());


}

void wjournal::on_resettingcelljournal_clicked()
{
      jmodel->revertAll();
}

void wjournal::on_resettingrowjournal_clicked()
{
    jmodel ->select();
}

void wjournal::on_potvergeniejournal_clicked()
{
    jmodel -> submitAll();
}

void wjournal::on_deletejournal_clicked()
{
    int selectedRow = ui->journal->currentIndex().row();
    if (selectedRow >=0){
        qDebug() << "deleting row:" << jmodel->removeRow(selectedRow);
    }
    else{
          QMessageBox::critical(this, "ошибка", "строки не помечены");
        qDebug() << "no row selected";
    }
}

//void wjournal::on_ttable_triggered()
//{

//select j.id, j.time_out, j.time_in, r.name, a.num from journal j join routes r on r.id = j.routes_id join auto a on a.id =j.auto_id order by id asc
//  // select a.id, a.num, a.mark, a.color, ap.fist_name from auto a join auto_personnel ap on ap.id=a.auto_personnel_id order by id asc
//   //select * from auto_personnel order by id asc
//   //select * from routes order by id asc
//}


void wjournal::on_printer_triggered()
{
    QString str;
   str.append("<html><head></head><body><center>"+QString("отчет таблица журнал маршрутов"));
   str.append("<table border=1><tr>");
   str.append("<td>"+QString("номер")+"</td>");
   str.append("<td>"+QString("отпрака")+"</td>");
   str.append("<td>"+QString("прибытие")+"</td>");
   str.append("<td>"+QString("улица")+"</td>");
   str.append("<td>"+QString("номер машины")+"</td></tr>");

   QSqlQuery* query = new QSqlQuery();
   query->exec("select j.id, j.time_out, j.time_in, r.name, a.num from journal j join routes r on r.id = j.routes_id join auto a on a.id =j.auto_id order by id asc");

   while(query->next())
   {
       str.append("<tr><td>");
       str.append(query->value(0).toString());
       str.append("</td><td>");
       str.append(query->value(1).toString());
       str.append("</td><td>");
       str.append(query->value(2).toString());
       str.append("</td><td>");
       str.append(query->value(3).toString());
       str.append("</td><td>");
       str.append(query->value(4).toString());
       str.append("</td></tr>");



   }
   str.append("</table></center></body></html>");

   QPrinter printer;
   printer.setOrientation(QPrinter::Portrait);
   printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setPaperSize(QPrinter::A4);

   QString path = QFileDialog::getSaveFileName(NULL,"соханить в pdf", "отчет журнал маршрутов", "PDF(*.pdf)");
   if(path.isEmpty())return;

   printer.setOutputFileName(path);

   QTextDocument doc;
   doc.setHtml(str);
   doc.print(&printer);
}
