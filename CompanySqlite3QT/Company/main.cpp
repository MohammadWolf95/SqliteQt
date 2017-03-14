#include <QApplication>
#include <sqlite3.h>
#include "company.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(company);
    QApplication a(argc, argv);
    Company *companyWidget=new Company;
    companyWidget->show();

    return a.exec();
}
