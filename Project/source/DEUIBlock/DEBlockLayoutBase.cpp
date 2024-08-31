#include "DEBlockLayoutBase.h"

DEBlockLayoutBase::DEBlockLayoutBase(QWidget* parent, QString BlockID, QString Label)
    : DEBlock(parent, BlockID, Label)
{

}

void DEBlockLayoutBase::SetExpanded(bool bExpand)
{
    DEBlock::SetExpanded(bExpand);
}

DEBlockBox* DEBlockLayoutBase::GetBlockBox()
{
    return nullptr;
}

void DEBlockLayoutBase::SetBackgroudColor(int type)
{
    DEBlock::SetBackgroudColor(type);
}

void DEBlockLayoutBase::SetEnable(bool bEnable)
{
    DEBlock::SetEnable(bEnable);
}

void DEBlockLayoutBase::SetShow(bool bShow)
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
