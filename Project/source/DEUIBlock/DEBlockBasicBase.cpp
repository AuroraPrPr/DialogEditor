#include "DEBlockBasicBase.h"
#include "DEBlockLayoutBase.h"

DEBlockBasicBase::DEBlockBasicBase(QWidget* parent, QString BlockID, QString Label)
    : DEBlock(parent, BlockID, Label)
{

}

void DEBlockBasicBase::SetBackgroudColor(int type)
{
    DEBlock::SetBackgroudColor(type);
    setAttribute(Qt::WA_StyledBackground);

    switch(type)
    {
    case 0:
        setStyleSheet("background: rgb(255, 255, 255)");
        break;
    case 1:
        setStyleSheet("background: rgb(218, 222, 255)");
        break;
    }
}

void DEBlockBasicBase::SetEnable(bool bEnable)
{
    DEBlock::SetEnable(bEnable);
}

void DEBlockBasicBase::SetShow(bool bShow)
{
    DEBlock::SetShow(bShow);

    if(b_Init)
    {
        DEBlock* Block = this;
        while(Block->GetParentLayout())
        {
            DEBlockLayoutBase* ParentLayout = (DEBlockLayoutBase*)Block->GetParentLayout();
            int width = ParentLayout->size().width();
            int Hbefore = ParentLayout->GetBlockBox()->size().height();
            ParentLayout->GetBlockBox()->adjustSize();
            int Hafter = ParentLayout->GetBlockBox()->size().height();
            ParentLayout->GetBlockBox()->resize(width, Hafter);

            QSize size = ParentLayout->size();
            int h = size.height() + Hafter - Hbefore;
            size.setHeight(h);
            ParentLayout->resize(size);
            Block = ParentLayout;
        }
    }
}
