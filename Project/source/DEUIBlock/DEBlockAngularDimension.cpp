#include "DEBlockAngularDimension.h"

DEBlockAngularDimension::DEBlockAngularDimension(QWidget* parent, QString BlockID, QString Label)
    : DEBlockDimension(parent, BlockID, Label)
{

}

void DEBlockAngularDimension::BlockInitialize()
{
    DEBlockDimension::BlockInitialize();
    SetUnit("°");
}

QString DEBlockAngularDimension::Type()
{
    return "AngularDimension";
}
