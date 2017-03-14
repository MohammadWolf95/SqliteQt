#include "addemployee.h"
#include "ui_addemployee.h"
#include <QtWidgets>
#include "sqlcompany.h"
#include "company.h"
#include "singletonpath.h"

addemployee::addemployee(QString nameTable,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addemployee)
{
    ui->setupUi(this);
    nameTable_=nameTable;
    listSubordinates=findChild<QListWidget*>("listViewSubordinates");

    Sqlcompany db(Singletonpath::getInstance().sqlpath);
    QByteArray nameTableBa=nameTable_.toLatin1();
    char*nameTableChar=nameTableBa.data();
    QStringList list=db.all_data(nameTableChar);
    listSubordinates->addItems(list);
}

addemployee::~addemployee()
{
    delete ui;
}
