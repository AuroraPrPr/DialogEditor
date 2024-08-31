#include "DEBlockLinearDimension.h"

DEBlockLinearDimension::DEBlockLinearDimension(QWidget* parent, QString BlockID, QString Label)
    : DEBlockDimension(parent, BlockID, Label)
{

}

void DEBlockLinearDimension::BlockInitialize()
{
    DEBlockDimension::BlockInitialize();
    SetUnit("mm");
}

QString DEBlockLinearDimension::Type()
{
    return "LinearDimension";
}
