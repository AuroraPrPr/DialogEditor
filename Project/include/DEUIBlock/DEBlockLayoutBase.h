#ifndef DEBLOCKLAYOUTBASE_H
#define DEBLOCKLAYOUTBASE_H

#include "DEUIBlock_global.h"
#include "DEBlock.h"
#include "DEBlockBox.h"

class DEUIBLOCK_EXPORT DEBlockLayoutBase : public DEBlock
{
public:
    explicit DEBlockLayoutBase(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

public:
    virtual void BlockInitialize() { DEBlock::BlockInitialize();};
    virtual QString Type() { return "";};
    virtual void SetExpanded(bool bExpand);
    virtual DEBlockBox* GetBlockBox();
    virtual void SetBackgroudColor(int type);
    virtual void SetEnable(bool bEnable);
    virtual void SetShow(bool bShow);
};

#endif // DEBLOCKLAYOUTBASE_H
