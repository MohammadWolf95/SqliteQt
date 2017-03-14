#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>
QT_FORWARD_DECLARE_CLASS(QListWidget)
QT_FORWARD_DECLARE_CLASS(QListWidgetItem)

namespace Ui {
class addemployee;
}

class addemployee : public QDialog
{
    Q_OBJECT

public:
    explicit addemployee(QString nameTable, QWidget *parent = 0);
    ~addemployee();
private:
    Ui::addemployee *ui;
    QString nameTable_;
    QListWidget*listSubordinates;
};

#endif // ADDEMPLOYEE_H
