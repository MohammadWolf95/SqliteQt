#ifndef COMPANY_H
#define COMPANY_H
#include <QWidget>
 #include <QDate>
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QDateEdit)

class Company:public QWidget{
    Q_OBJECT
public:
    Company(QWidget*parent=0);
    ~Company();
private slots:
    void editDb_clicked();
    void calculationSalary();
    void calculationTatalGain();
private:
    QWidget*loadUiFile();
    QString calcSalaryEmp(const QDate&currentDate,
                      const QDate&enrDate,
                      QString &salary);    //функция для вычисления зарплаты Employee

    QString calcSalaryMan(const QDate&currentDate,
                        const QDate&enrDate,
                        QString &salary,
                        QString &name);    //функция для вычисления зарплаты Manager

    QString calcSalarySal(const QDate&currentDate,
                          const QDate&enrDate,
                          QString &salary,
                          QString &name);    //функция для вычисления зарплаты Sales

    void openFile();

    QPushButton*ui_pushDbEdit;
    QPushButton*ui_pushCalculation;
    QPushButton*ui_pushTotalGain;
    QPushButton*ui_pushOpenFile;

    QLineEdit*ui_lineSelection;
    QLineEdit*ui_lineCalculation;
    QLineEdit*ui_lineTotalGain;

    QDateEdit*ui_dateWork;

    QDate currentDate;  //текущая дата
    QDate enrdate;      //дата вступления на работу
};

#endif // COMPANY_H
