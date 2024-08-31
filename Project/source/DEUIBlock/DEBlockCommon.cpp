#include "DEBlockCommon.h"

#include "DEBlockBox.h"

DEUIBLOCK_EXPORT DEBlock* CreateBlock(QWidget* pParent, QString type, QString blockID, QString label)
{
    DEBlock* pBlock = nullptr;
    //基本
    if(type == "Label")
    {
        pBlock = new DEBlockLabel(pParent, blockID, label);
    }
    else if(type == "Enumeration")
    {
        pBlock = new DEBlockEnumeration(pParent, blockID, label);
    }
    else if(type == "Toggle")
    {
        pBlock = new DEBlockToggle(pParent, blockID, label);
    }
    else if(type == "Integer")
    {
        pBlock = new DEBlockInt(pParent, blockID, label);
    }
    else if(type == "Double")
    {
        pBlock = new DEBlockDouble(pParent, blockID, label);
    }
    else if(type == "LinearDimension")
    {
        pBlock = new DEBlockLinearDimension(pParent, blockID, label);
    }
    else if(type == "AngularDimension")
    {
        pBlock = new DEBlockAngularDimension(pParent, blockID, label);
    }
    else if(type == "RadiusDimension")
    {
        pBlock = new DEBlockRadiusDimension(pParent, blockID, label);
    }
    else if(type == "Group")
    {
        pBlock = new DEBlockGroup(pParent, blockID, label);
    }
    else if(type == "SelectObject")
    {
        pBlock = new DEBlockObject(pParent, blockID, label);
    }

    return pBlock;
}

DEUIBLOCK_EXPORT void AddBlockToContainer(DEBlockContainer* pContainer, DEBlock* pBlock)
{
    if(!pContainer || !pBlock)
        return;

    if (pBlock->Type() == "Group")
    {
        pContainer->GetBlockBox()->AddBlockToBox(pBlock);
        pBlock->SetContainer(pContainer);
        pContainer->AddBlock(pBlock);
    }
    else
    {
        if (!pBlock->Group())
        {
            //正常添加
            pContainer->GetBlockBox()->AddBlockToBox(pBlock);
        }
        else
        {
            DEBlockGroup* group = new DEBlockGroup(pBlock->GetDialog(), "", pBlock->Label());
            group->SetBackgroudColor(1);
            pBlock->SetBackgroudColor(1);

            group->GetBlockBox()->AddBlockToBox(pBlock);
            group->SetContainer(pContainer);
            pBlock->SetGroupLayout(group);
            pContainer->GetBlockBox()->AddBlockToBox(group);
        }

        pBlock->SetContainer(pContainer);
        pContainer->AddBlock(pBlock);
    }
}

DEUIBLOCK_EXPORT void AddBlockToContainer(DEBlockContainer* pContainer, DEBlock* pBlock, int row, int column)
{
    if(!pContainer || !pBlock)
        return;

    if (pBlock->Type() == "Group")
    {
        pContainer->GetBlockBox()->AddBlockToBox(pBlock, row, column);
        pBlock->SetContainer(pContainer);
        pContainer->AddBlock(pBlock);
    }
    else
    {
        if (!pBlock->Group())
        {
            //正常添加
            pContainer->GetBlockBox()->AddBlockToBox(pBlock, row, column);
        }
        else
        {
            DEBlockGroup* group = new DEBlockGroup(pBlock->GetDialog(), pBlock->Label());
            group->SetBackgroudColor(1);
            pBlock->SetBackgroudColor(1);

            group->GetBlockBox()->AddBlockToBox(pBlock);
            group->SetContainer(pContainer);
            pBlock->SetGroupLayout(group);
            pContainer->GetBlockBox()->AddBlockToBox(group, row, column);
        }

        pBlock->SetContainer(pContainer);
        pContainer->AddBlock(pBlock);
    }
}

DEUIBLOCK_EXPORT void AddLayoutToContainer(DEBlockContainer* pContainer, DEBlockLayoutBase* pBlock)
{
    if (!pContainer || !pBlock)
        return;

    pContainer->GetBlockBox()->AddBlockToBox(pBlock);
    pBlock->SetContainer(pContainer);
    pContainer->AddBlock(pBlock);
}

DEUIBLOCK_EXPORT void AddLayoutToContainer(DEBlockContainer* pContainer, DEBlockLayoutBase* pBlock, int row, int column)
{
    if (!pContainer || !pBlock)
        return;

    pContainer->GetBlockBox()->AddBlockToBox(pBlock, row, column);
    pBlock->SetContainer(pContainer);
    pContainer->AddBlock(pBlock);
}

DEUIBLOCK_EXPORT void AddBlockToLayout(DEBlockContainer* pContainer, DEBlockLayoutBase* pLayout, DEBlock* pBlock)
{
    if(!pContainer || !pLayout || !pBlock)
        return;

    int color = 0;
    int layoutcolor = pLayout->GetBackgroudColor();
    if(layoutcolor == 0)
        color = 1;

    if(!pBlock->Group())
    {
        //正常添加
        pBlock->SetBackgroudColor(layoutcolor);
        pLayout->GetBlockBox()->AddBlockToBox(pBlock);
    }
    else
    {
        DEBlockGroup* group = new DEBlockGroup(pBlock->GetDialog(), pBlock->Label());
        group->SetBackgroudColor(color);
        pBlock->SetBackgroudColor(color);

        group->GetBlockBox()->AddBlockToBox(pBlock);
        group->SetContainer(pContainer);
        group->SetParentLayout(pLayout);
        pBlock->SetGroupLayout(group);
        pLayout->GetBlockBox()->AddBlockToBox(group);
    }

    pBlock->SetContainer(pContainer);
    pBlock->SetParentLayout(pLayout);
    pContainer->AddBlock(pBlock);
}
DEUIBLOCK_EXPORT void AddBlockToLayout(DEBlockContainer* pContainer, DEBlockLayoutBase* pLayout, DEBlock* pBlock, int row, int column)
{
    if(!pContainer || !pLayout || !pBlock)
        return;

    int color = 0;
    int layoutcolor = pLayout->GetBackgroudColor();
    if(layoutcolor == 0)
        color = 1;

    if(!pBlock->Group())
    {
        //正常添加
        pBlock->SetBackgroudColor(layoutcolor);
        pLayout->GetBlockBox()->AddBlockToBox(pBlock);
    }
    else
    {
        DEBlockGroup* group = new DEBlockGroup(pBlock->GetDialog(), pBlock->Label());
        group->SetBackgroudColor(color);
        pBlock->SetBackgroudColor(color);

        group->GetBlockBox()->AddBlockToBox(pBlock);
        group->SetContainer(pContainer);
        group->SetParentLayout(pLayout);
        pBlock->SetGroupLayout(group);
        pLayout->GetBlockBox()->AddBlockToBox(group, row, column);
    }

    pBlock->SetContainer(pContainer);
    pBlock->SetParentLayout(pLayout);
    pContainer->AddBlock(pBlock);
}

DEUIBLOCK_EXPORT void AddLayoutToLayout(DEBlockContainer* pContainer, DEBlockLayoutBase* pLayout, DEBlockLayoutBase* pBlock)
{
    if(!pContainer || !pLayout || !pBlock)
        return;

    int color = 0;
    int layoutcolor = pLayout->GetBackgroudColor();
    if(layoutcolor == 0)
        color = 1;

    pBlock->SetBackgroudColor(color);
    pLayout->GetBlockBox()->AddBlockToBox(pBlock);

    pBlock->SetContainer(pContainer);
    pBlock->SetParentLayout(pLayout);
    pContainer->AddBlock(pBlock);
}
DEUIBLOCK_EXPORT void AddLayoutToLayout(DEBlockContainer* pContainer, DEBlockLayoutBase* pLayout, DEBlockLayoutBase* pBlock, int row, int column)
{
    if(!pContainer || !pLayout || !pBlock)
        return;

    int color = 0;
    int layoutcolor = pLayout->GetBackgroudColor();
    if(layoutcolor == 0)
        color = 1;

    pBlock->SetBackgroudColor(color);
    pLayout->GetBlockBox()->AddBlockToBox(pBlock, row, column);

    pBlock->SetContainer(pContainer);
    pBlock->SetParentLayout(pLayout);
    pContainer->AddBlock(pBlock);
}
