#include "sqlcompany.h"
#include <QtWidgets>

static QString dataTable;

Sqlcompany::Sqlcompany(const QString&fileName)
{
    this->fileName=fileName;
}

Sqlcompany::~Sqlcompany(){
}

static int callback(void *NotUsed, int argc, char **argv,
                    char **azColName);

QStringList Sqlcompany::sql_inquiry(char*column_argv[],
                             int argc,
                             char*param_bind,const char*employeeName, char*table_name){
    sqlite3 *db;
    sqlite3_stmt *res;
    QStringList listParameters;


    QByteArray ba=fileName.toLatin1();
    const char*path_sql=ba.data();
    int rc = sqlite3_open(path_sql, &db);

    if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return listParameters;
    }

    char sqlCharArray[200]= "SELECT ";
        for(int i=0; i<argc; i++){
            if(i==(argc-1)){
                strcat(sqlCharArray,column_argv[i]);
                break;
            }
            strcat(sqlCharArray,column_argv[i]);
            strcat(sqlCharArray,", ");
        }
    strcat(sqlCharArray, " FROM ");
    strcat(sqlCharArray,table_name);
    strcat(sqlCharArray," WHERE ");
    strcat(sqlCharArray,param_bind);
    strcat(sqlCharArray, " = ?");

    rc = sqlite3_prepare_v2(db, sqlCharArray, -1, &res, 0);

    if (rc == SQLITE_OK){
        sqlite3_bind_text(res, 1, employeeName,-1,0);
    }
    else{
        qDebug()<<"Failed to execute statement: "<<sqlite3_errmsg(db)<<endl;
    }

    int step = sqlite3_step(res);
    if (step == SQLITE_ROW){
        for(int i=0;i<argc;i++){
            //qDebug("%s: ", sqlite3_column_text(res, i));
            const unsigned char* unsStr=sqlite3_column_text(res, i);
            const char*str;
            str=reinterpret_cast<const char*>(unsStr);
            QString qstr=QString::fromUtf8(str);
            listParameters.append(qstr);
        }
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return listParameters;
}

QStringList Sqlcompany::all_data(char*table_name){
    sqlite3 *db;
    QStringList list;
    char *err_msg = 0;

    dataTable.clear();
    QByteArray ba = fileName.toLatin1();
    const char*path_str=ba.data();

    int rc = sqlite3_open(path_str, &db);

    if (rc != SQLITE_OK){
        list<<"Cannot open database: "<<sqlite3_errmsg(db);
        sqlite3_close(db);
        return list;
    }

    char sql[200]="SELECT * FROM ";
    strcat(sql, table_name);

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK ){
        qDebug("Failed to select data\n");
        qDebug("SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
    }
    //Linkedlist list;
    list=dataTable.split('\n');
    list.removeLast(); //нужно удалить последний элемент, т.к. он равен просто \n
    sqlite3_close(db);
    return list;
}

static int callback(void *NotUsed, int argc, char **argv,
                    char **azColName)
{
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {

        QString str=QString(argv[i] ? argv[i] : "NULL");
        if(i==argc-1){
            str+='\n';
        }
        else{
            str+=" ";
        }

        dataTable+=str;
    }

    return 0;
}
