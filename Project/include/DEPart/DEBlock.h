#ifndef DEBLOCK_H
#define DEBLOCK_H

#include "DEPart_global.h"
#include <QWidget>
#include <QLabel>
#include "DECommon.h"

class DEBlockContainer;
class DEPART_EXPORT DEBlock : public QWidget
{
public:
    explicit DEBlock(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");
    virtual ~DEBlock();

public://内部调用的函数
    virtual void BlockInitialize();

    void SetContainer(DEBlockContainer* Container);
    void SetParentLayout(DEBlock* pParentLayout);
    void SetGroupLayout(DEBlock* pGroup);
    DEBlockContainer* GetContainer() {return m_pContainer;};
    DEBlock* GetParentLayout() {return m_pParentLayout;};
    QWidget* GetDialog() {return m_pDialog;};

    virtual void SetCtrlActive() {};
    virtual void SetCtrlEnd() {};

    virtual void SetBackgroudColor(int type);
    inline int GetBackgroudColor() {return i_BackgroudColorType;};

    virtual void SetVisible(bool bShow);

public:
    virtual QString Type();
    virtual QString Name();
    virtual void SetName(QString BlockID);
    virtual bool Enable();
    virtual void SetEnable(bool bEnable);
    virtual bool Expand();
    virtual void SetExpanded(bool expanded);
    virtual bool Group();
    virtual void SetGroup(bool bGroup);
    virtual QString Label();
    virtual void SetLabel(QString label);
    virtual void SetLabel(const char* label);
    virtual bool Show();
    virtual void SetShow(bool bShow);

protected:
    QWidget* m_pWidget;                      //自己
    QWidget* m_pDialog;                      //控件所在对话框
    QString s_Label;                         //控件标签内容
    QString s_BlockID;                       //控件ID
    bool b_Enable = true;
    bool b_Expanded = true;
    bool b_Group = false;
    bool b_Show = true;
    bool b_Init = false;
    //上下左右
protected:
    QLabel* m_pLabel;
protected:
    //布局控件调整高度时需要一起调整
    DEBlockContainer* m_pContainer;
    DEBlock* m_pParentLayout;

    DEBlock* m_pGroup;

    //操作结束还原样式
    QString m_StyleSheet;
    int i_BackgroudColorType = 0;
};

#endif // DEBLOCK_H
