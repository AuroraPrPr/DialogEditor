#include "DEBlockInt.h"
#include "DECtrlLineEdit.h"

DEBlockInt::DEBlockInt(QWidget* parent, QString BlockID, QString Label)
    : DEBlockNumBase(parent, BlockID, Label)
{
    i_Style = Keyin;
    b_LabelVisible = true;
    b_ReadOnly = false;
    m_iValue = 0;
    m_iStep = 1;

    //Keyin
    m_pLineEdit = new DECtrlLineEdit();
    m_pLineEdit->setFixedHeight(28);
    m_pLineEdit->setValidator(new QIntValidator(this));
    m_pLineEdit->setAlignment(Qt::AlignRight);
    connect(m_pLineEdit, &QLineEdit::editingFinished,
            this, &DEBlockInt::KeyinValueChanged);

    //Spin
    m_pSpinBox = new QSpinBox();
    m_pSpinBox->setFixedHeight(28);
    m_pSpinBox->setCursor(Qt::IBeamCursor);
    m_pSpinBox->setRange(INT_MIN, INT_MAX);
    m_pSpinBox->setAlignment(Qt::AlignRight);
    connect(m_pSpinBox, &QSpinBox::editingFinished,
            this, &DEBlockInt::SpinValueChanged);
}

DEBlockInt::~DEBlockInt()
{
    if(m_pLineEdit) {delete m_pLineEdit; m_pLineEdit = nullptr;}
    if(m_pSpinBox) {delete m_pSpinBox; m_pSpinBox = nullptr;}
}

void DEBlockInt::BlockInitialize()
{
    DEBlock::BlockInitialize();

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(6, 0, 4, 0);

    switch (i_Style)
    {
    case Keyin:
    {
        if(b_LabelVisible)
        {
            layout->addWidget(m_pLabel);
            m_pLineEdit->setFixedWidth(100);
            layout->addWidget(m_pLineEdit, Qt::AlignRight);
        }
        else
        {
            layout->addWidget(m_pLineEdit);
        }

        m_pWidget->setLayout(layout);
        m_pWidget->setFixedHeight(BlockHeight);

        m_pLineEdit->setText(QString::number(m_iValue));
        m_pLineEdit->setReadOnly(b_ReadOnly);
        break;
    }
    case Spin:
    {
        if(b_LabelVisible)
        {
            layout->addWidget(m_pLabel);
            m_pSpinBox->setFixedWidth(100);
            layout->addWidget(m_pSpinBox, Qt::AlignRight);
        }
        else
        {
            layout->addWidget(m_pSpinBox);
        }
        m_pWidget->setLayout(layout);
        m_pWidget->setFixedHeight(BlockHeight);

        m_pSpinBox->setValue(m_iValue);
        m_pSpinBox->setSingleStep(m_iStep);
        m_pSpinBox->setReadOnly(b_ReadOnly);
        break;
    }
    default:
        break;
    }
}

QString DEBlockInt::Type()
{
    return "Integer";
}

void DEBlockInt::SetEnable(bool bEnable)
{
    DEBlockNumBase::SetEnable(bEnable);
    m_pLineEdit->setEnabled(bEnable);
    m_pSpinBox->setEnabled(bEnable);
}

void DEBlockInt::SetPresentationStyle(PresentationStyle style)
{
    i_Style = style;
}
PresentationStyle DEBlockInt::GetPresentationStyle()
{
    return i_Style;
}

void DEBlockInt::SetValue(int value)
{
    m_iValue = value;
    if(b_Init)
    {
        switch (i_Style)
        {
        case Keyin:
        {
            m_pLineEdit->setText(QString::number(m_iValue));
            break;
        }
        case Spin:
        {
            m_pSpinBox->setValue(m_iValue);
            break;
        }
        }
    }
}
int DEBlockInt::GetValue()
{
    return m_iValue;
}

void DEBlockInt::SetLabelVisibility(bool bVisible)
{
    b_LabelVisible = bVisible;
}
bool DEBlockInt::GetLabelVisibility()
{
    return b_LabelVisible;
}

void DEBlockInt::SetReadOnly(bool bReadOnly)
{
    b_ReadOnly = bReadOnly;
}
bool DEBlockInt::GetReadOnly()
{
    return b_ReadOnly;
}

void DEBlockInt::SetStep(int step)
{
    m_iStep = step;
    m_pSpinBox->setSingleStep(m_iStep);
}
int DEBlockInt::GetStep()
{
    return m_iStep;
}

void DEBlockInt::SetCallBackFun_ValueChanged(CallBack1 pFun)
{
    m_pValueChanged = pFun;
}

void DEBlockInt::KeyinValueChanged()
{
    m_iValue = m_pLineEdit->text().toInt();
    if(m_pValueChanged)
        m_pValueChanged(m_pDialog);
}

void DEBlockInt::SpinValueChanged()
{
    m_iValue = m_pSpinBox->value();
    if(m_pValueChanged)
        m_pValueChanged(m_pDialog);
}
