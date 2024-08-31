#ifndef DEBLOCKANGULARDIMENSION_H
#define DEBLOCKANGULARDIMENSION_H

#include "DEBlockDimension.h"

class DEUIBLOCK_EXPORT DEBlockAngularDimension : public DEBlockDimension
{
public:
    explicit DEBlockAngularDimension(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

    virtual void BlockInitialize();
    virtual QString Type();
};

#endif // DEBLOCKANGULARDIMENSION_H
