#ifndef DEBLOCKNUMBASE_H
#define DEBLOCKNUMBASE_H

#include "DEUIBlock_global.h"
#include "DEBlock.h"

class DEUIBLOCK_EXPORT DEBlockNumBase : public DEBlock
{
public:
    explicit DEBlockNumBase(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

public:
    virtual void BlockInitialize() { DEBlock::BlockInitialize();};
    virtual QString Type() { return "";};
    virtual void SetBackgroudColor(int type);
    virtual void SetEnable(bool bEnable);
    virtual void SetShow(bool bShow);
};

enum PresentationStyle
{
    Keyin,
    Spin,
    //Combo
};

#endif // DEBLOCKNUMBASE_H
