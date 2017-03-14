#include "company.h"
#include <QtUiTools>
#include "editdb.h"
#include "sqlcompany.h"
#include "str_switch.h"
#include "singletonpath.h"

Company::Company(QWidget*parent)
    :QWidget(parent)
{
    QWidget*formWidget=loadUiFile();

    ui_pushDbEdit=findChild<QPushButton*>("pushDbEdit");
    ui_pushDbEdit->setEnabled(false);
    ui_pushCalculation=findChild<QPushButton*>("pushCalculation");
    ui_pushCalculation->setEnabled(false);
    ui_pushTotalGain=findChild<QPushButton*>("pushTotalGain");
    ui_pushTotalGain->setEnabled(false);
    ui_pushOpenFile=findChild<QPushButton*>("pushOpenFile");

    ui_lineSelection=findChild<QLineEdit*>("lineSelection");
    ui_lineCalculation=findChild<QLineEdit*>("lineCalculation");
    ui_lineCalculation->setReadOnly(true);
    ui_lineTotalGain=findChild<QLineEdit*>("lineTotalGain");

    ui_dateWork=findChild<QDateEdit*>("dateWork");

    connect(ui_pushDbEdit, &QPushButton::clicked, this, &Company::editDb_clicked);
    connect(ui_pushCalculation, &QPushButton::clicked, this, &Company::calculationSalary);
    connect(ui_pushTotalGain, &QPushButton::clicked, this, &Company::calculationTatalGain);
    connect(ui_pushOpenFile, &QPushButton::clicked, this, &Company::openFile);

    QGridLayout*layout=new QGridLayout(this);
    layout->addWidget(formWidget);
    setLayout(layout);
    setWindowTitle(tr("Payroll"));
}

Company::~Company(){

}

void Company::editDb_clicked(){
   Editdb*newWindowDbEdit=new Editdb(this);
   newWindowDbEdit->show();
   newWindowDbEdit->setWindowTitle(tr("Edit db"));
}

QWidget* Company::loadUiFile()
{
    QUiLoader loader;

    QFile file(":/forms/company.ui");
    file.open(QFile::ReadOnly);

    QWidget*formWidget=loader.load(&file, this);
    file.close();
    return formWidget;
}

QString Company::calcSalaryEmp(const QDate&currentDate,
                           const QDate&enrDate,
                           QString&salary)
{
    int experience=currentDate.year()-enrDate.year();
    float sal=salary.toFloat();
    float allowance;    //надбавка
    float max_allowance=(sal/100)*30;    //max надбавка
    if(enrDate.month()==12||currentDate.month()<enrDate.month()){
        if(experience==0){
            return salary;
        }else{
            allowance=(sal/100)*3*(experience-1);
        }
    }else{
        allowance=(sal/100)*3*experience;
    }
    if(allowance>max_allowance){
        sal+=max_allowance;
    }else{
        sal+=allowance;
    }
    salary.setNum(sal);
    return salary;
}

void Company::openFile(){
    const QStringList documentsPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString filePath =
              QFileDialog::getOpenFileName(this, tr("Open File"),
                                           documentsPaths.isEmpty() ? QDir::homePath() : documentsPaths.first(),
                                           tr("DataBase files (*.db);;All files (*.*)"));


    if(!filePath.isEmpty()){
        Singletonpath::getInstance().sqlpath=filePath;

        ui_pushDbEdit->setEnabled(true);
        ui_pushCalculation->setEnabled(true);
        ui_pushTotalGain->setEnabled(true);
    }
}

QString Company::calcSalaryMan(const QDate&currentDate,
                    const QDate&enrDate,
                    QString &salary,
                    QString &name)
{
    Sqlcompany db(Singletonpath::getInstance().sqlpath);

    QByteArray ba = name.toLatin1();
    char *name_char = ba.data();

    float interest=0; //проценты от подчиненных

    QStringList list=db.all_data(name_char);
    QVector<QStringList>paramSubList;  //это вектор для параметров подчиненных

    for(auto str:list){
        QStringList list_param=str.split(" ");
        paramSubList.push_back(list_param);
    }
    for(QVector<QStringList>::iterator it=paramSubList.begin();
        it!=paramSubList.end();it++)
    {
        QDate subdate=QDate::fromString(it->at(3),"dd-MM-yyyy");
        if(it->at(2)=="Employee"&&subdate<currentDate){ //если сотрудник Employee
                                                        //и дата вступления на работу меньше
                                                        //текущей даты
                                                        //, то берем из него 0,5%
            float percent=0;
            float sal=it->at(4).toFloat();
            percent=sal/100*0.5;
            interest+=percent;
        }
    }
    int experience=currentDate.year()-enrDate.year();   //стаж работы

    float sal=salary.toFloat();
    float allowance;    //надбавка
    float max_allowance=(sal/100)*40;    //max надбавка
    if(enrDate.month()==12||currentDate.month()<enrDate.month())//Если сотрудник вступил
                                                                //на работу в декабре или
                                                                //текущий месяц меньше
                                                                //месяца вступления на работу
    {
        if(experience==0){  //нет надбавки, т.к. стаж работы равен 0
            sal+=interest;
            salary.setNum(sal);
            return salary;
        }
        else
        {
            allowance=(sal/100)*5*(experience-1);
        }
    }
    else
    {
        allowance=(sal/100)*5*experience;
    }

    sal+=interest;

    if(allowance>max_allowance){
        sal+=max_allowance;
    }
    else
    {
        sal+=allowance;
    }
    salary.setNum(sal);
    return salary;
}

QString Company::calcSalarySal(const QDate&currentDate,
                      const QDate&enrDate,
                      QString &salary,
                      QString &name){
    Sqlcompany db(Singletonpath::getInstance().sqlpath);

    QByteArray ba = name.toLatin1();
    char *name_char = ba.data();
    float interest=0; //проценты от подчиненных

    QStringList list=db.all_data(name_char);
    QVector<QStringList>paramSubList;  //это вектор для параметров подчиненных

    for(auto str:list){
        QStringList list_param=str.split(" ");
        paramSubList.push_back(list_param);
    }
    for(QVector<QStringList>::iterator it=paramSubList.begin();
        it!=paramSubList.end();it++)
    {
        QDate subdate=QDate::fromString(it->at(3),"dd-MM-yyyy");
        if(subdate<currentDate){    //проверяем дату вступления на работу подчиненного
            float percent=0;
            float sal=it->at(4).toFloat();
            percent=sal/100*0.3;
            interest+=percent;
        }
    }
    int experience=currentDate.year()-enrDate.year();   //стаж работы

    float sal=salary.toFloat();
    float allowance;    //надбавка
    float max_allowance=(sal/100)*35;    //max надбавка
    if(enrDate.month()==12||currentDate.month()<enrDate.month())//Если сотрудник вступил
                                                                //на работу в декабре или
                                                                //текущий месяц меньше
                                                                //месяца вступления на работу
    {
        if(experience==0){  //нет надбавки, т.к. стаж работы равен 0
            sal+=interest;
            salary.setNum(sal);
            return salary;
        }
        else
        {
            allowance=(sal/100)*(experience-1);
        }
    }
    else
    {
        allowance=(sal/100)*experience;
    }

    sal+=interest;

    if(allowance>max_allowance){
        sal+=max_allowance;
    }
    else
    {
        sal+=allowance;
    }
    salary.setNum(sal);
    return salary;
}

void Company::calculationSalary(){
    if(ui_lineSelection->text()==0){
        ui_lineCalculation->setText("Error: Enter the name of the employee");
        return;
    }
    QString str=ui_lineSelection->text();
    QByteArray ba=str.toLatin1();
    char*name=ba.data();
    Sqlcompany db(Singletonpath::getInstance().sqlpath);
    char*parameters[4]={"NAME", "ENRDATE", "POSITION", "SALARY"};
    QStringList inquiry=db.sql_inquiry(parameters, 4, "NAME", name); //это запрос 4-х параметров

    currentDate=ui_dateWork->date();

    enrdate=QDate::fromString(inquiry[1],"dd-MM-yyyy");

    if(currentDate<enrdate){
        ui_lineCalculation->setText("Error: employee came to work later");
        return;
    }

    QString salary=inquiry[3];
    SWITCH(inquiry[2].toLocal8Bit().constData()){
    CASE ("Employee"):
        calcSalaryEmp(currentDate,enrdate,salary);
        ui_lineCalculation->setText(salary);
        break;
    CASE ("Manager"):
        calcSalaryMan(currentDate,enrdate,salary,inquiry[0]);
        ui_lineCalculation->setText(salary);
        break;
    CASE ("Sales"):
        calcSalarySal(currentDate,enrdate,salary,inquiry[0]);
        ui_lineCalculation->setText(salary);
        break;
    }
}

void Company::calculationTatalGain(){
    Sqlcompany db(Singletonpath::getInstance().sqlpath);
    float totalGain=0;    //зарплата всех сотрудников
    QString totalGainStr;
    QStringList list=db.all_data();
    currentDate=ui_dateWork->date();
    QVector<QStringList>paramSubList;  //это вектор для параметров подчиненных

    for(auto str:list){
        QStringList list_param=str.split(" ");
        paramSubList.push_back(list_param);
    }

    for(QVector<QStringList>::iterator it=paramSubList.begin();
        it!=paramSubList.end();it++)
    {
        enrdate=QDate::fromString(it->at(3),"dd-MM-yyyy");
        QString salary=it->at(4);
        QString name=it->at(1);
        if(currentDate<enrdate){
            //ui_lineCalculation->setText("Error: employee came to work later");
            continue;
        }
        SWITCH(it->at(2).toLocal8Bit().constData()){
        CASE ("Employee"):
            calcSalaryEmp(currentDate,enrdate,salary);
            totalGain+=salary.toFloat();
            break;
        CASE ("Manager"):
            calcSalaryMan(currentDate,enrdate,salary,name);
            totalGain+=salary.toFloat();
            break;
        CASE ("Sales"):
            calcSalarySal(currentDate,enrdate,salary,name);
            totalGain+=salary.toFloat();
            break;
        }
    }
    totalGainStr.setNum(totalGain);
    ui_lineTotalGain->setText(totalGainStr);
}
