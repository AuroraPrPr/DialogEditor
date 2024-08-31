#ifndef DEBLOCKDOUBLE_H
#define DEBLOCKDOUBLE_H

#include "DEBlockNumBase.h"

class DECtrlLineEdit;

class DEUIBLOCK_EXPORT DEBlockDouble : public DEBlockNumBase
{
    Q_OBJECT
public:
    explicit DEBlockDouble(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");
    ~DEBlockDouble();

    virtual void BlockInitialize();
public:
    virtual QString Type();
    virtual void SetEnable(bool bEnable);

public:
    void SetPresentationStyle(PresentationStyle style);
    PresentationStyle GetPresentationStyle();

    void SetValue(double value);
    double GetValue();

    void SetLabelVisibility(bool bVisible);
    bool GetLabelVisibility();

    void SetReadOnly(bool bReadOnly);
    bool GetReadOnly();

    void SetStep(double step);
    double GetStep();

public slots:
    void KeyinValueChanged();
    void SpinValueChanged();
public://回调
    CallBack1 m_pValueChanged = nullptr;
    void SetCallBackFun_ValueChanged(CallBack1 pFun);

private:
    DECtrlLineEdit* m_pLineEdit;
    QDoubleSpinBox* m_pSpinBox;

private:
    PresentationStyle i_Style;
    bool b_LabelVisible;
    bool b_ReadOnly;

    double m_dValue;
    double m_dStep;
};

#endif // DEBLOCKDOUBLE_H
