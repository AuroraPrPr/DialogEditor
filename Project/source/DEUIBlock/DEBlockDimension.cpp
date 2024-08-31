#include "DEBlockDimension.h"
#include "DECtrlLineEdit.h"

DEBlockDimension::DEBlockDimension(QWidget* parent, QString BlockID, QString Label)
    : DEBlockNumBase(parent, BlockID, Label)
{
    m_pLineEdit = new DECtrlLineEdit(this);
    m_pLineEdit->setFixedWidth(100);
    m_pLineEdit->setStyleSheet(R"(QLineEdit
                                  {
                                  border: none;
                                  selection-background-color: #9BBBF7;
                                  selection-color: #000;
                                  })");
    connect(m_pLineEdit, &QLineEdit::editingFinished,
            this, &DEBlockDimension::ValueChanged);

    m_pRightPart = new QWidget(this);
    m_pRightPart->setStyleSheet("border: 1px solid gray;");

    m_pUnit = new QLabel(this);
    m_pUnit->setFixedWidth(31);
    m_pUnit->setStyleSheet(QString(R"(
                                   QLabel{
                                   border-left: none;
                                   border-right: none;
                                   border-top: 1px solid gray;
                                   border-bottom: 1px solid gray;
                                   }
                                   )"));
    QFont font;
    font.setFamily(tr("微软雅黑"));
    font.setPointSize(8);
    m_pUnit->setFont(font);
    m_pUnit->setAlignment(Qt::AlignCenter);

    m_pButton = new QPushButton();
    m_pButton->setFixedWidth(12);
    m_pButton->setStyleSheet(QString(R"(
                                     QPushButton{
                                     border: none;
                                     }
                                     QPushButton::menu-indicator{
                                     subcontrol-position: center center;
                                     }
                                     )"));

    QMenu* menu = new QMenu(m_pButton);
    menu->setStyleSheet(QString(R"(
                                QMenu::item:selected {
                                background-color: #C1D1B8;
                                }
                                )"));

    QAction* action1 = new QAction(tr("测量"), menu);
    menu->addAction(action1);

    QAction* action2 = new QAction(tr("公式"), menu);
    menu->addAction(action2);

    QAction* action3 = new QAction(tr("函数"), menu);
    menu->addAction(action3);

    QAction* action4 = new QAction(tr("表达式"), menu);
    menu->addAction(action4);

    m_pButton->setMenu(menu);
}

DEBlockDimension::~DEBlockDimension()
{

}

void DEBlockDimension::BlockInitialize()
{
    DEBlockNumBase::BlockInitialize();

    QHBoxLayout* layout1 = new QHBoxLayout(this);
    layout1->setSpacing(0);
    layout1->setContentsMargins(6, 0, 4, 0);

    QHBoxLayout* layout2 = new QHBoxLayout(this);
    layout2->setSpacing(0);
    layout2->setContentsMargins(1, 0, 1, 0);

    layout2->addWidget(m_pLineEdit);
    layout2->addWidget(m_pUnit);
    layout2->addWidget(m_pButton);
    m_pRightPart->setLayout(layout2);
    m_pRightPart->setFixedSize(145, 28);
    m_pRightPart->setStyleSheet("border: 1px solid gray;");

    layout1->addWidget(m_pLabel);
    layout1->addWidget(m_pRightPart, Qt::AlignRight);
    m_pWidget->setLayout(layout1);
    m_pWidget->setFixedHeight(30);
}

QString DEBlockDimension::Type()
{
    return "";
}

void DEBlockDimension::SetBackgroudColor(int type)
{
    DEBlockNumBase::SetBackgroudColor(type);
    setAttribute(Qt::WA_StyledBackground);
    switch(type)
    {
    case 0:
        setStyleSheet("background: rgb(255, 255, 255)");
        m_pLabel->setStyleSheet("background: rgb(255, 255, 255)");
        m_pRightPart->setStyleSheet("background: rgb(255, 255, 255)");
        break;
    case 1:
        setStyleSheet("background: rgb(218, 222, 255)");
        m_pLabel->setStyleSheet("background: rgb(218, 222, 255)");
        m_pRightPart->setStyleSheet("background: rgb(218, 222, 255)");
        break;
    }
}

void DEBlockDimension::SetEnable(bool bEnable)
{
    DEBlockNumBase::SetEnable(bEnable);
    m_pLineEdit->setEnabled(bEnable);
    m_pUnit->setEnabled(bEnable);
    m_pButton->setEnabled(bEnable);
}

void DEBlockDimension::SetValue(double value)
{
    m_pLineEdit->setText(QString::number(value));
}
double DEBlockDimension::GetValue()
{
    QString value = GetFormula();
    return value.toDouble();
}

void DEBlockDimension::SetUnit(QString unit)
{
    m_pUnit->setText(unit);
}
QString DEBlockDimension::GetUnit()
{
    return m_pUnit->text();
}

void DEBlockDimension::SetFormula(QString value)
{
    m_pLineEdit->setText(value);
}
void DEBlockDimension::SetFormula(const char* value)
{
    m_pLineEdit->setText(value);
}
QString DEBlockDimension::GetFormula()
{
    return m_pLineEdit->text();
}

void DEBlockDimension::SetCallBackFun_ValueChanged(CallBack1 pFun)
{
    m_pValueChanged = pFun;
}

void DEBlockDimension::ValueChanged()
{
    if(m_pValueChanged)
        m_pValueChanged(m_pDialog);
}
