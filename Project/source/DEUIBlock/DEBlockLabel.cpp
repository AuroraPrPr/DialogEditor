#include "DEBlockLabel.h"

DEBlockLabel::DEBlockLabel(QWidget* parent, QString BlockID, QString Label)
    : DEBlockBasicBase(parent, BlockID, Label)
{
    m_pHLayout = new QHBoxLayout(this);
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(6, 0, 4, 0);
}

void DEBlockLabel::BlockInitialize()
{
    DEBlockBasicBase::BlockInitialize();
    m_pHLayout->addWidget(m_pLabel);
    m_pWidget->setLayout(m_pHLayout);
    m_pWidget->setFixedHeight(BlockHeight);
}

QString DEBlockLabel::Type()
{
    return "Label";
}
