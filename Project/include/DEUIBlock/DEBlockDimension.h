#ifndef DEBLOCKDIMENSION_H
#define DEBLOCKDIMENSION_H

#include "DEBlockNumBase.h"

class DECtrlLineEdit;

class DEUIBLOCK_EXPORT DEBlockDimension : public DEBlockNumBase
{
    Q_OBJECT
public:
    explicit DEBlockDimension(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");
    ~DEBlockDimension();

    virtual void BlockInitialize();
public:
    virtual QString Type();
    virtual void SetBackgroudColor(int type);
    virtual void SetEnable(bool bEnable);

public:
    void SetValue(double value);
    double GetValue();

    void SetUnit(QString unit = "mm");
    QString GetUnit();

    void SetFormula(QString value);
    void SetFormula(const char* value);
    QString GetFormula();

public slots:
    void ValueChanged();
public://回调
    CallBack1 m_pValueChanged = nullptr;
    void SetCallBackFun_ValueChanged(CallBack1 pFun);
private:
    DECtrlLineEdit* m_pLineEdit;
    QLabel* m_pUnit;
    QPushButton* m_pButton;
    QWidget* m_pRightPart;
};

#endif // DEBLOCKDIMENSION_H
