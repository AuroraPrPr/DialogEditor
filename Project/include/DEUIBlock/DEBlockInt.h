#ifndef DEBLOCKINT_H
#define DEBLOCKINT_H

#include "DEBlockNumBase.h"

class DECtrlLineEdit;

class DEUIBLOCK_EXPORT DEBlockInt : public DEBlockNumBase
{
    Q_OBJECT
public:
    explicit DEBlockInt(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");
    ~DEBlockInt();

    virtual void BlockInitialize();
public:
    virtual QString Type();
    virtual void SetEnable(bool bEnable);

public:
    void SetPresentationStyle(PresentationStyle style);
    PresentationStyle GetPresentationStyle();

    void SetValue(int value);
    int GetValue();

    void SetLabelVisibility(bool bVisible);
    bool GetLabelVisibility();

    void SetReadOnly(bool bReadOnly);
    bool GetReadOnly();

    void SetStep(int step);
    int GetStep();

public slots:
    void KeyinValueChanged();
    void SpinValueChanged();
public://回调
    CallBack1 m_pValueChanged = nullptr;
    void SetCallBackFun_ValueChanged(CallBack1 pFun);

private:
    DECtrlLineEdit* m_pLineEdit;
    QSpinBox* m_pSpinBox;

private:
    PresentationStyle i_Style;
    bool b_LabelVisible;
    bool b_ReadOnly;

    int m_iValue;
    int m_iStep;
};

#endif // DEBLOCKINT_H
