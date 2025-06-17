#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QDialog>

const int BUTTON_NUM = 16;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
     void calc_slot();


private:
    Ui::Dialog *m_ui;
    bool m_calculated ;
    bool m_justCalculated ;
    QString m_first_Operand;
    QString m_second_Operand;
    QChar m_operand;
};

#endif // MAINWINDOW_H
