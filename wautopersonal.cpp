#include "wautopersonal.h"
#include "ui_wautopersonal.h"
#include "mainwindow.h"
#include "vavto.h"
#include "wjournal.h"
#include<QtSql/QSqlRelationalDelegate>
#include <QDebug>
#include <QMessageBox>
#include "wroutes.h"
#include "spravka.h"
#include "info.h"
#include <QPrinter>
#include<QTextDocument>
#include<QFileDialog>
#include<QtSql/QSqlQuery>
#include<QStringList>


wautopersonal::wautopersonal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wautopersonal)
{
    ui->setupUi(this);

 ui->comboBox->addItems(QStringList()<<"Минимальная"<<"Средняя"<<"Максимальмальная"<<"Всего");

 sal.insert("Минимальная", "min");
 sal.insert("Средняя", "avg");
 sal.insert("Максимальмальная", "max");
 sal.insert("Всего", "sum");

 apmodel = new QSqlRelationalTableModel (/*this, db*/);
 apmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
 apmodel -> setEditStrategy(QSqlTableModel::OnManualSubmit);
 apmodel -> setTable("auto_personnel");
 apmodel -> select();
 ui->personal->setModel(apmodel);
 ui -> personal-> setItemDelegate(new QSqlRelationalDelegate(ui->personal));
}

wautopersonal::~wautopersonal()
{
    delete ui;
}

void wautopersonal::on_avtor_triggered()
{
    hide();
    MainWindow* window = new MainWindow(this);
       window->show();
}

void wautopersonal::on_journal_triggered()
{
    hide();
    wjournal* window = new wjournal(this);
       window->show();
}

void wautopersonal::on_avto_triggered()
{
    hide();
    vavto* window = new vavto(this);
       window->show();
}

void wautopersonal::on_routes_triggered()
{
    hide();
    wroutes* window = new wroutes(this);
       window->show();
}

void wautopersonal::on_spravka_triggered()
{
    spravka* window = new spravka(this);
       window->show();
}

void wautopersonal::on_info_triggered()
{
    info* window = new info(this);
       window->show();
}



void wautopersonal::on_addrowpersonal_clicked()
{
     qDebug() << "inserting row" << apmodel -> insertRow(apmodel ->rowCount());
}

void wautopersonal::on_resettingcellpersonal_clicked()
{
     apmodel->revertAll();
}

void wautopersonal::on_resettingrowpersonal_clicked()
{
     apmodel ->select();
}

void wautopersonal::on_potvergeniepersonal_clicked()
{
    apmodel -> submitAll();
}

void wautopersonal::on_deletepersonal_clicked()
{
    int selectedRow = ui->personal->currentIndex().row();
    if (selectedRow >=0){
        qDebug() << "deleting row:" << apmodel->removeRow(selectedRow);
    }
    else{
          QMessageBox::critical(this, "ошибка", "строки не помечены");
        qDebug() << "no row selected";
    }
}

void wautopersonal::on_printer_triggered()
{
    QString str;
   str.append("<html><head></head><body><center>"+QString("отчет таблица персонал"));
   str.append("<table border=1><tr>");
   str.append("<td>"+QString("номер")+"</td>");
   str.append("<td>"+QString("имя")+"</td>");
   str.append("<td>"+QString("фамилия")+"</td>");
   str.append("<td>"+QString("отчество")+"</td></tr>");


   QSqlQuery* query = new QSqlQuery();
   query->exec("select * from auto_personnel order by id asc");

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
       str.append("</td></tr>");

   }
   str.append("</table></center></body></html>");

   QPrinter printer;
   printer.setOrientation(QPrinter::Portrait);
   printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setPaperSize(QPrinter::A4);

   QString path = QFileDialog::getSaveFileName(NULL,"соханить в pdf", "отчет персонал", "PDF(*.pdf)");
   if(path.isEmpty())return;

   printer.setOutputFileName(path);

   QTextDocument doc;
   doc.setHtml(str);
   doc.print(&printer);
}

void wautopersonal::on_pushButton_clicked()
{


        salary = new QSqlQueryModel();
    salary->setQuery("select "+sal.value(ui->comboBox->currentText())+"(salary) from auto_personnel");
    ui->tableView->setModel(salary);
     ui->tableView->show();


}
