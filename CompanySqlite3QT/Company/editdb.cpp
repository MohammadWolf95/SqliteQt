#include "editdb.h"
#include "ui_editdb.h"
#include "addemployee.h"
#include "sqlite3.h"
#include "sqlcompany.h"
#include <QtWidgets>
#include "company.h"
#include "singletonpath.h"

Editdb::Editdb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editdb)
{
    ui->setupUi(this);

    listEmployees=findChild<QListWidget*>("listWidget");

    Sqlcompany db(Singletonpath::getInstance().sqlpath);
    char*parameters[5]={"ID", "NAME", "ENRDATE", "POSITION", "SALARY"};
    db.sql_inquiry(parameters, 5, "NAME", "Alex");
    QStringList list=db.all_data();
    listEmployees->addItems(list);

    connect(listEmployees, &QListWidget::itemDoubleClicked,
            this, &Editdb::listSubordinates);

    //QListWidget::itemClicked()
}

Editdb::~Editdb()
{
    delete ui;
}

void Editdb::listSubordinates(QListWidgetItem*item){
    QString str=item->text();
    QVector<QString>stringVector(5);
    int k=0;

    for(int i=0;i<str.count();i++){
        if(str.at(i)==' '){
            k++;
            i++;
        }
        stringVector[k]+=str.at(i);
    }
    addemployee*newWindowAddEmp=new addemployee(stringVector[1],this);
    newWindowAddEmp->show();
    newWindowAddEmp->setWindowTitle(tr("Add Employee"));
}
