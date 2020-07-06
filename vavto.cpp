#include "vavto.h"
#include "ui_vavto.h"
#include "mainwindow.h"
#include "wjournal.h"
#include<QtSql/QSqlRelationalDelegate>
#include <QDebug>
#include <QMessageBox>
#include "wautopersonal.h"
#include "wroutes.h"
#include "spravka.h"
#include "info.h"
#include <QPrinter>
#include<QTextDocument>
#include<QFileDialog>
#include<QtSql/QSqlQuery>


vavto::vavto(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::vavto)
{
    ui->setupUi(this);
}

vavto::~vavto()
{
    delete ui;
}

void vavto::on_avtor_triggered()
{
    hide();
    MainWindow* window = new MainWindow(this);
       window->show();
}

void vavto::on_wjournal_triggered()
{
    hide();
    wjournal* window = new wjournal(this);
       window->show();
}

void vavto::on_personal_triggered()
{
    hide();
    wautopersonal* window = new wautopersonal(this);
       window->show();
}

void vavto::on_routes_triggered()
{
    hide();
    wroutes* window = new wroutes(this);
       window->show();
}

void vavto::on_spravka_triggered()
{
    spravka* window = new spravka(this);
       window->show();
}

void vavto::on_info_triggered()
{
    info* window = new info(this);
       window->show();
}


void vavto::on_vstavkadata_clicked()
{
    amodel = new QSqlRelationalTableModel (/*this, db*/);
    amodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    amodel -> setEditStrategy(QSqlTableModel::OnManualSubmit);
    amodel -> setTable("auto");
    amodel -> setRelation(amodel->fieldIndex("auto_personnel_id"),
                             QSqlRelation("auto_personnel","id", "fist_name"));
    amodel -> select ();
    ui->auto_2->setModel(amodel);
    ui -> auto_2-> setItemDelegate(new QSqlRelationalDelegate(ui->auto_2));

}

void vavto::on_auto_2_clicked(const QModelIndex &index)
{
    int temp_nom = ui->auto_2->model()->data(ui->auto_2->model()->index(index.row(),0)).toInt();
    ui->aid->setText(QString::number(temp_nom));

    QString temp_nom2 = ui->auto_2->model()->data(ui->auto_2->model()->index(index.row(),1)).toString();
    ui->num->setText(temp_nom2);

    QString temp_nom3 = ui->auto_2->model()->data(ui->auto_2->model()->index(index.row(),2)).toString();
    ui->marka->setText(temp_nom3);

    QString temp_nom4 = ui->auto_2->model()->data(ui->auto_2->model()->index(index.row(),3)).toString();
    ui->color->setText(temp_nom4);

    QString temp_nom5 = ui->auto_2->model()->data(ui->auto_2->model()->index(index.row(),4)).toString();
    ui->personnel->setText(temp_nom5);
}

void vavto::on_addrowauto_clicked()
{
   qDebug() << "inserting row" << amodel -> insertRow(amodel ->rowCount());
}

void vavto::on_resettingcellauto_clicked()
{
    amodel->revertAll();
}

void vavto::on_resettingrowauto_clicked()
{
    amodel ->select();
}

void vavto::on_potvergenieauto_clicked()
{
    amodel -> submitAll();
}

void vavto::on_deleteauto_clicked()
{
    int selectedRow = ui->auto_2->currentIndex().row();
    if (selectedRow >=0){
        qDebug() << "deleting row:" << amodel->removeRow(selectedRow);
    }
    else{
        QMessageBox::critical(this, "ошибка", "строки не помечены");
        qDebug() << "no row selected";
    }
}

void vavto::on_printer_triggered()
{
    QString str;
   str.append("<html><head></head><body><center>"+QString("отчет таблица авто"));
   str.append("<table border=1><tr>");
   str.append("<td>"+QString("номер")+"</td>");
   str.append("<td>"+QString("номер машины")+"</td>");
   str.append("<td>"+QString("марка")+"</td>");
   str.append("<td>"+QString("цвет")+"</td>");
   str.append("<td>"+QString("имя водителя")+"</td></tr>");

   QSqlQuery* query = new QSqlQuery();
   query->exec("select a.id, a.num, a.mark, a.color, ap.fist_name from auto a join auto_personnel ap on ap.id=a.auto_personnel_id order by id asc");

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

   QString path = QFileDialog::getSaveFileName(NULL,"соханить в pdf", "отчет авто", "PDF(*.pdf)");
   if(path.isEmpty())return;

   printer.setOutputFileName(path);

   QTextDocument doc;
   doc.setHtml(str);
   doc.print(&printer);
}
