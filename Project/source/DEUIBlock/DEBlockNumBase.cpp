#include "DEBlockNumBase.h"
#include "DEBlockLayoutBase.h"

DEBlockNumBase::DEBlockNumBase(QWidget* parent, QString BlockID, QString Label)
    : DEBlock(parent, BlockID, Label)
{

}

void DEBlockNumBase::SetBackgroudColor(int type)
{
    DEBlock::SetBackgroudColor(type);
}

void DEBlockNumBase::SetEnable(bool bEnable)
{
    DEBlock::SetEnable(bEnable);
}

void DEBlockNumBase::SetShow(bool bShow)
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
