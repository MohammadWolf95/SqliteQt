#ifndef EDITDB_H
#define EDITDB_H

#include <QDialog>
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QListWidget)
QT_FORWARD_DECLARE_CLASS(QListWidgetItem)

namespace Ui {
class Editdb;
}

class Editdb : public QDialog
{
    Q_OBJECT

public:
    explicit Editdb(QWidget *parent = 0);
    ~Editdb();

private slots:
    void listSubordinates(QListWidgetItem*);

private:
    Ui::Editdb *ui;
    QListWidget*listEmployees;
    //static const QString pathWithApp;
    //QByteArray ba=pathWithApp.toLatin1();
    //char*pathWithAppCh=ba.data();
};

#endif // EDITDB_H
