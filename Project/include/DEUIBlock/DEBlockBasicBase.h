#ifndef DEBLOCKBASICBASE_H
#define DEBLOCKBASICBASE_H

#include "DEUIBlock_global.h"
#include "DEBlock.h"

class DEUIBLOCK_EXPORT DEBlockBasicBase : public DEBlock
{
public:
    explicit DEBlockBasicBase(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

public:
    virtual void BlockInitialize() { DEBlock::BlockInitialize();};
    virtual QString Type() { return "";};
    virtual void SetBackgroudColor(int type);
    virtual void SetEnable(bool bEnable);
    virtual void SetShow(bool bShow);
};

#endif // DEBLOCKBASICBASE_H
