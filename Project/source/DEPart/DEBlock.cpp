#include "DEBlock.h"
#include "DEBlockContainer.h"

DEBlock::DEBlock(QWidget* parent, QString BlockID, QString Label)
    : QWidget(parent)
{
    m_pWidget = this;
    m_pDialog = parent;
    s_Label = Label;
    s_BlockID = BlockID;
    m_pLabel = new QLabel(s_Label);

    m_pContainer = nullptr;
    m_pParentLayout = nullptr;
    m_pGroup = nullptr;

    setAttribute(Qt::WA_StyledBackground);
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setStyleSheet("background: rgb(255, 255, 255)");
}

DEBlock::~DEBlock()
{

}

void DEBlock::BlockInitialize()
{
    b_Init = true;
}

void DEBlock::SetContainer(DEBlockContainer* Container)
{
    m_pContainer = Container;
}

void DEBlock::SetParentLayout(DEBlock* pParentLayout)
{
    m_pParentLayout = pParentLayout;
}

void DEBlock::SetBackgroudColor(int type)
{
    i_BackgroudColorType = type;

    setAttribute(Qt::WA_StyledBackground);
    switch(type)
    {
    case 0:
        setStyleSheet("backgroud-color: rgb(255, 255, 255)");
        break;
    case 1:
        setStyleSheet("backgroud-color: rgb(218, 240, 255)");
        break;
    case 2://天蓝色
        setStyleSheet("backgroud-color: rgb(135, 206, 250)");
        break;
    }
}

QString DEBlock::Type()
{
    return "";
}

QString DEBlock::Name()
{
    return s_BlockID;
}
void DEBlock::SetName(QString BlockID)
{
    s_BlockID = BlockID;
}

bool DEBlock::Enable()
{
    return b_Enable;
}
void DEBlock::SetEnable(bool bEnable)
{
    b_Enable = bEnable;
}

bool DEBlock::Expand()
{
    return b_Expanded;
}
void DEBlock::SetExpanded(bool expanded)
{
    b_Expanded = expanded;
}

bool DEBlock::Group()
{
    return b_Group;
}
void DEBlock::SetGroup(bool bGroup)
{
    b_Group = bGroup;
}

QString DEBlock::Label()
{
    return s_Label;
}
void DEBlock::SetLabel(QString label)
{
    s_Label = label;
    m_pLabel->setText(s_Label);
}
void DEBlock::SetLabel(const char* label)
{
    s_Label = label;
    m_pLabel->setText(s_Label);
}

bool DEBlock::Show()
{
    return b_Show;
}
void DEBlock::SetShow(bool bShow)
{
    b_Show = bShow;
    SetVisible(b_Show);
}

void DEBlock::SetVisible(bool bShow)
{
    setVisible(bShow);
    if(b_Group && m_pGroup)
        m_pGroup->setVisible(bShow);
}

void DEBlock::SetGroupLayout(DEBlock* pGroup)
{
    m_pGroup = pGroup;
}
