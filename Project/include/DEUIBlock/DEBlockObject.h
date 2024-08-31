#ifndef DEBLOCKOBJECT_H
#define DEBLOCKOBJECT_H

#include "DEBlockSelectBase.h"

class DEUIBLOCK_EXPORT DEBlockObject : public DEBlockSelectBase
{
public:
    explicit DEBlockObject(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

    virtual void BlockInitialize();
public:
    virtual QString Type();
    virtual void SetEnable(bool bEnable);

private:
    QLabel* m_pIcon;

};
#endif // DEBLOCKOBJECT_H
