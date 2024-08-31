#ifndef DEBLOCKTOGGLE_H
#define DEBLOCKTOGGLE_H

#include "DEBlockBasicBase.h"

class DEUIBLOCK_EXPORT DEBlockToggle : public DEBlockBasicBase
{
    Q_OBJECT
public:
    explicit DEBlockToggle(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

    virtual void BlockInitialize();
public:
    virtual QString Type();
    virtual void SetLabel(QString label);
    virtual void SetLabel(const char* label);
public:
    int Value();
    void SetValue(int value);
    void SetValue(bool bChecked);

public slots:
    void CheckBoxStateChanged();
public://回调
    CallBack1 m_pToggleValueChanged = nullptr;
    void SetCallBackFun_ToggleValueChanged(CallBack1 pFun);
private:
    QCheckBox* m_pCheckBox;
    QHBoxLayout* m_pHLayout;

private:
    bool b_Checked = false;
};

#endif // DEBLOCKTOGGLE_H
