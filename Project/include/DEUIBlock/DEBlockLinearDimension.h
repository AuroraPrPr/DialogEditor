#ifndef DEBLOCKLINEARDIMENSION_H
#define DEBLOCKLINEARDIMENSION_H

#include "DEBlockDimension.h"

class DEUIBLOCK_EXPORT DEBlockLinearDimension : public DEBlockDimension
{
public:
    explicit DEBlockLinearDimension(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

    virtual void BlockInitialize();
    virtual QString Type();
};

#endif // DEBLOCKLINEARDIMENSION_H
