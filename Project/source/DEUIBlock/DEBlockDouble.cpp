#include "DEBlockDouble.h"
#include "DECtrlLineEdit.h"

DEBlockDouble::DEBlockDouble(QWidget* parent, QString BlockID, QString Label)
    : DEBlockNumBase(parent, BlockID, Label)
{
    i_Style = Keyin;
    b_LabelVisible = true;
    b_ReadOnly = false;
    m_dValue = 0.000;
    m_dStep = 1;

    //Keyin
    m_pLineEdit = new DECtrlLineEdit();
    m_pLineEdit->setFixedHeight(28);
    m_pLineEdit->setValidator(new QDoubleValidator(this));
    m_pLineEdit->setAlignment(Qt::AlignRight);
    connect(m_pLineEdit, &QLineEdit::editingFinished,
            this, &DEBlockDouble::KeyinValueChanged);

    //Spin
    m_pSpinBox = new QDoubleSpinBox();
    m_pSpinBox->setFixedHeight(28);
    m_pSpinBox->setCursor(Qt::IBeamCursor);
    m_pSpinBox->setDecimals(3);//保留3位小数
    m_pSpinBox->setRange(INT_MIN, INT_MAX);
    m_pSpinBox->setAlignment(Qt::AlignRight);
    connect(m_pSpinBox, &QSpinBox::editingFinished,
            this, &DEBlockDouble::SpinValueChanged);
}

DEBlockDouble::~DEBlockDouble()
{
    if(m_pLineEdit) {delete m_pLineEdit; m_pLineEdit = nullptr;}
    if(m_pSpinBox) {delete m_pSpinBox; m_pSpinBox = nullptr;}
}

void DEBlockDouble::BlockInitialize()
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

        m_pLineEdit->setText(QString::number(m_dValue));
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

        m_pSpinBox->setValue(m_dValue);
        m_pSpinBox->setSingleStep(m_dStep);
        m_pSpinBox->setReadOnly(b_ReadOnly);
        break;
    }
    default:
        break;
    }
}

QString DEBlockDouble::Type()
{
    return "Double";
}

void DEBlockDouble::SetEnable(bool bEnable)
{
    DEBlockNumBase::SetEnable(bEnable);
    m_pLineEdit->setEnabled(bEnable);
    m_pSpinBox->setEnabled(bEnable);
}

void DEBlockDouble::SetPresentationStyle(PresentationStyle style)
{
    i_Style = style;
}
PresentationStyle DEBlockDouble::GetPresentationStyle()
{
    return i_Style;
}

void DEBlockDouble::SetValue(double value)
{
    m_dValue = value;
    if(b_Init)
    {
        switch (i_Style)
        {
        case Keyin:
        {
            m_pLineEdit->setText(QString::number(m_dValue));
            break;
        }
        case Spin:
        {
            m_pSpinBox->setValue(m_dValue);
            break;
        }
        }
    }
}
double DEBlockDouble::GetValue()
{
    return m_dValue;
}

void DEBlockDouble::SetLabelVisibility(bool bVisible)
{
    b_LabelVisible = bVisible;
}
bool DEBlockDouble::GetLabelVisibility()
{
    return b_LabelVisible;
}

void DEBlockDouble::SetReadOnly(bool bReadOnly)
{
    b_ReadOnly = bReadOnly;
}
bool DEBlockDouble::GetReadOnly()
{
    return b_ReadOnly;
}

void DEBlockDouble::SetStep(double step)
{
    m_dStep = step;
    m_pSpinBox->setSingleStep(m_dStep);
}
double DEBlockDouble::GetStep()
{
    return m_dStep;
}

void DEBlockDouble::SetCallBackFun_ValueChanged(CallBack1 pFun)
{
    m_pValueChanged = pFun;
}

void DEBlockDouble::KeyinValueChanged()
{
    m_dValue = m_pLineEdit->text().toDouble();
    if(m_pValueChanged)
        m_pValueChanged(m_pDialog);
}

void DEBlockDouble::SpinValueChanged()
{
    m_dValue = m_pSpinBox->value();
    if(m_pValueChanged)
        m_pValueChanged(m_pDialog);
}
