#ifndef SQLCOMPANY_H
#define SQLCOMPANY_H
#include "sqlite3.h"
#include <QWidget>

#include <qfile.h>
#include <qtextstream.h>

class Sqlcompany{
public:
    Sqlcompany(const QString&fileName); //здесь нужно указать полный путь к файлу! Например: C:/Users/Magomed/Documents/QT/CompanyKaliningrad/Company/db/company.db
    ~Sqlcompany();
    QStringList sql_inquiry(char*column_argv[],
                     int argc,
                     char*param_bind,const char*employeeName, char*table_name="COMPANY");   //вызов №2
    QStringList all_data(char*table_name="COMPANY");    //это запрос всех параметров,
                                                        //0-ID,
                                                        //1-NAME,
                                                        //2-POSITION
                                                        //3-ENRDATE
                                                        //4-SALARY
    QString array_db;
private:
    QString fileName;
};

#endif // SQLCOMPANY_H
