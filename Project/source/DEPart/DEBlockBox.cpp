#include "DEBlockBox.h"
#include "DEBlock.h"

DEBlockBox::DEBlockBox(QWidget *parent) : QWidget(parent)
{
    m_pLayout = new QGridLayout;
    i_Column = 1;
}

DEBlockBox::~DEBlockBox()
{

}

void DEBlockBox::AddBlockToBox(DEBlock* Ctrl)
{
    m_pLayout->addWidget(Ctrl);
    this->setLayout(m_pLayout);
}

void DEBlockBox::AddBlockToBox(DEBlock* Ctrl, int row, int column)
{
    if(column == -1)
    {
        m_pLayout->addWidget(Ctrl, row, 0, 1, -1);//覆盖一行
    }
    else
    {
        m_pLayout->addWidget(Ctrl, row, column);
    }
    this->setLayout(m_pLayout);
}

void DEBlockBox::SetBlockBoxMargin(int type)
{
    switch(type)
    {
    case 0:
        m_pLayout->setSpacing(2);
        m_pLayout->setContentsMargins(2, 0, 2, 0);
        break;
    case 1:
        m_pLayout->setSpacing(1);
        m_pLayout->setContentsMargins(6, 4, 4, 4);
        break;
    }
}

void DEBlockBox::SetColumnNum(int Column)
{
    i_Column = Column;
}
