#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Dialog),
    m_calculated(false),
    m_justCalculated(false)
{
    m_ui->setupUi(this);
    m_ui->lineEdit->setText("0");
    m_ui->lineEdit->setAlignment(Qt::AlignRight);

    for (int i = 1; i <= BUTTON_NUM; ++i)
    {
        QString name = QString("pushButton_%1").arg(i);
        QPushButton *btn = findChild<QPushButton*>(name);
        if (btn)
        {
            connect(btn, SIGNAL(clicked()), this, SLOT(calc_slot()));
        }
    }
}


Dialog::~Dialog()
{
    delete m_ui;
}


void Dialog::calc_slot()
{
    QPushButton *button_tmp = qobject_cast<QPushButton *>(sender());
    if(!button_tmp || !m_ui->lineEdit)
    {
        qDebug() << "ERROR";
        return;
    }

    QChar char_tmp = button_tmp->text()[0];
    QString str_tmp;

    qDebug() << "button_tmp!" << button_tmp->text();
    qDebug() << "lineEdit!" << m_ui->lineEdit->text();
    qDebug() << "char_tmp" << char_tmp;

    if (char_tmp.isDigit()) {
        qDebug() << "isDigit!";
        if (m_calculated || m_justCalculated) {
            m_second_Operand.clear();
            m_justCalculated = false;
            m_calculated = false;
        }

        if (m_ui->lineEdit->text() == "0" && m_operand.isNull()) {
            str_tmp = button_tmp->text();
            m_first_Operand = str_tmp;
        } else {
            if (!m_operand.isNull()) {
                m_second_Operand += button_tmp->text();
                str_tmp = m_second_Operand;
            } else {
                m_first_Operand += button_tmp->text();
                str_tmp = m_first_Operand;
            }
        }
    }

    if (char_tmp.isPunct() || char_tmp.isSymbol()) {
        qDebug() << "isSymbol!";
        bool ok1, ok2;

        if (m_first_Operand.isEmpty())
            m_first_Operand = "0";

        if (m_calculated && char_tmp != '=') {
            m_second_Operand.clear();
        }

        if (!m_second_Operand.isEmpty()) {
            double a = m_first_Operand.toDouble(&ok1);
            double b = m_second_Operand.toDouble(&ok2);
            if (!ok1 || !ok2) {
                str_tmp = "Error";
            } else {
                switch (m_operand.toLatin1()) {
                    case '+': str_tmp = QString::number(a + b); break;
                    case '-': str_tmp = QString::number(a - b); break;
                    case '*': str_tmp = QString::number(a * b); break;
                    case '/': str_tmp = (b != 0.0) ? QString::number(a / b) : "Error"; break;
                }
                m_first_Operand = str_tmp;
                m_justCalculated = true;
            }
        }

        if (char_tmp != '=') {
            m_operand = char_tmp;
        } else {
            m_calculated = true;
        }
    }

    if (char_tmp.isLetter()) {
        qDebug() << "isLetter!";
        str_tmp = "0";
        m_first_Operand.clear();
        m_second_Operand.clear();
        m_operand = 0;
        m_calculated = false;
        m_justCalculated = false;
    }

    if (str_tmp.isEmpty()) {
        if (!m_second_Operand.isEmpty())
            str_tmp = m_second_Operand;
        else
            str_tmp = m_first_Operand;
    }

    m_ui->lineEdit->setText(str_tmp);
    m_ui->lineEdit->setAlignment(Qt::AlignRight);
}



