#ifndef DEBLOCKRADIUSDIMENSION_H
#define DEBLOCKRADIUSDIMENSION_H

#include "DEBlockDimension.h"

class DEUIBLOCK_EXPORT DEBlockRadiusDimension : public DEBlockDimension
{
public:
    explicit DEBlockRadiusDimension(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

    virtual void BlockInitialize();
    virtual QString Type();
};

#endif // DEBLOCKRADIUSDIMENSION_H
