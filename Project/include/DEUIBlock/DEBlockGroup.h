#ifndef DEBLOCKGROUP_H
#define DEBLOCKGROUP_H
#include "DEBlockLayoutBase.h"
class DEBlockBox;

class DEUIBLOCK_EXPORT DEBlockGroup: public DEBlockLayoutBase
{
public:
    explicit DEBlockGroup(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");

    virtual void BlockInitialize();
public:
    virtual QString Type();
    virtual void SetBackgroudColor(int type);
    virtual void SetEnable(bool bEnable);
    virtual void SetExpanded(bool bExpand);
    virtual DEBlockBox* GetBlockBox();
public:
    void AdjustHeight();
    void SetIcon();

    int Column();
    void SetColumn(int num);

    void stateSwitch();
protected:
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
private:
    QWidget* m_Bar;
    QHBoxLayout* m_BarLayout;
    QLabel* m_BarLabel;
    QLabel* m_BarIcon;
    DEBlockBox* m_pCtrlBox;
    QVBoxLayout* m_Layout;

private:
    QString m_LabelStyleSheet;

};

#endif // DEBLOCKGROUP_H
