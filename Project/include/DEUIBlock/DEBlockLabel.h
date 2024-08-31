#ifndef DEBLOCKLABEL_H
#define DEBLOCKLABEL_H

#include "DEBlockBasicBase.h"

class DEUIBLOCK_EXPORT DEBlockLabel : public DEBlockBasicBase
{
public:
    explicit DEBlockLabel(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

    virtual void BlockInitialize();

public:
    virtual QString Type();

private:
    QHBoxLayout* m_pHLayout;
};

#endif // DEBLOCKLABEL_H
