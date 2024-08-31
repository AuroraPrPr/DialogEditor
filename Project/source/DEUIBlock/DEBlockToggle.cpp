#include "DEBlockToggle.h"

DEBlockToggle::DEBlockToggle(QWidget* parent, QString BlockID, QString Label)
    : DEBlockBasicBase(parent, BlockID, Label)
{
    m_pCheckBox = new QCheckBox(Label, this);

    m_pHLayout = new QHBoxLayout();
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(6, 0, 4, 0);
}

void DEBlockToggle::BlockInitialize()
{
    DEBlockBasicBase::BlockInitialize();
    m_pCheckBox->setCheckState(Qt::Unchecked);
    if(b_Checked)
        m_pCheckBox->setCheckState(Qt::Checked);

    m_pHLayout->addWidget(m_pCheckBox);
    m_pWidget->setLayout(m_pHLayout);
    m_pWidget->setFixedHeight(BlockHeight);

    m_pLabel->setVisible(false);

    connect(m_pCheckBox, &QCheckBox::stateChanged,
            this, &DEBlockToggle::CheckBoxStateChanged);
}

QString DEBlockToggle::Type()
{
    return "Toggle";
}

void DEBlockToggle::SetLabel(QString label)
{
    DEBlock::SetLabel(label);
    m_pCheckBox->setText(label);
}

void DEBlockToggle::SetLabel(const char* label)
{
    DEBlock::SetLabel(label);
    m_pCheckBox->setText(label);
}

int DEBlockToggle::Value()
{
    return b_Checked;
}

void DEBlockToggle::SetValue(int value)
{
    if(value == 0 || 1)
    {
        b_Checked = value;
        if(value == 0)
            m_pCheckBox->setCheckState(Qt::Unchecked);
        else
            m_pCheckBox->setCheckState(Qt::Checked);
    }
}
void DEBlockToggle::SetValue(bool bChecked)
{
    b_Checked = bChecked;
    if(bChecked)
        m_pCheckBox->setCheckState(Qt::Checked);
    else
        m_pCheckBox->setCheckState(Qt::Unchecked);
}

void DEBlockToggle::SetCallBackFun_ToggleValueChanged(CallBack1 pFun)
{
    m_pToggleValueChanged = pFun;
}

void DEBlockToggle::CheckBoxStateChanged()
{
    if(m_pToggleValueChanged)
        m_pToggleValueChanged(m_pDialog);
}
