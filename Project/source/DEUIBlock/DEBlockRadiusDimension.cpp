#include "DEBlockRadiusDimension.h"

DEBlockRadiusDimension::DEBlockRadiusDimension(QWidget* parent, QString BlockID, QString Label)
    : DEBlockDimension(parent, BlockID, Label)
{

}

void DEBlockRadiusDimension::BlockInitialize()
{
    DEBlockDimension::BlockInitialize();
    SetUnit("mm");
}

QString DEBlockRadiusDimension::Type()
{
    return "RadiusDimension";
}
