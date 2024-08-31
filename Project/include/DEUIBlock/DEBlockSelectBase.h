#ifndef DEBLOCKSELECTBASE_H
#define DEBLOCKSELECTBASE_H

#include "DEUIBlock_global.h"
#include "DEBlock.h"

enum StepStatus
{
    Required = 0,
    Optional,
    SatisFied
};

enum SelectMode
{
    Single,
    Multiple
};

class DEUIBLOCK_EXPORT DEBlockSelectBase : public DEBlock
{
    Q_OBJECT
public:
    explicit DEBlockSelectBase(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

public:
    virtual void BlockInitialize();
    virtual void SetCtrlActive();
    virtual void SetCtrlEnd();
    virtual QString Type() { return "";};
    virtual void SetBackgroudColor(int type);
    virtual void SetEnable(bool bEnable);
    virtual void SetShow(bool bShow);
    bool eventFilter(QObject* watched, QEvent* event);
public:
    void StepStatusChanged(StepStatus step);
    StepStatus GetStatusChanged();

    void SetSelectMode(SelectMode mode);
    SelectMode GetSelectMode();

    void SetResultNum(int num);

signals:
    void SelectBlockActive();

protected:
    QWidget* m_pLabelWrap;
    QLabel* m_pResultIcon;

protected:
    StepStatus m_StepStatus;
    SelectMode m_SelectMode;

    QString s_ActiveStyleSheet;      //激活样式
    QString s_UnActiveStyleSheet;    //未激活样式
    QString s_StyleSheet;            //保存样式
};

#endif // DEBLOCKSELECTBASE_H
