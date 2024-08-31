#ifndef DEBLOCKENUMERATION_H
#define DEBLOCKENUMERATION_H

#include "DEBlockBasicBase.h"

enum EnumerationStyle
{
    OptionMenu,
    RadioBox,
    PullDown
};

enum RadioBoxLayoutStyle
{
    vertical,
    horizontal
};

class DEUIBLOCK_EXPORT DEBlockEnumeration : public DEBlockBasicBase
{
    Q_OBJECT
public:
    explicit DEBlockEnumeration(QWidget* parent = nullptr, QString BlockID = "", QString Label = "");
    ~DEBlockEnumeration();

    virtual void BlockInitialize();
public:
    virtual QString Type();
    virtual void SetBackgroudColor(int type);
    virtual void SetEnable(bool bEnable);

public:
    void SetEnumerationStyle(EnumerationStyle style);
    EnumerationStyle GetnumerationStyle();

    void SetCurIndex(int index);
    int GetCurIndex();

    void SetLabelVisibility(bool bVisible);
    bool GetLabelVisibility();

    void SetBitmaps(QStringList Icons);
    QStringList GetBitmaps();

    void SetEnumMembers(QStringList members);
    QStringList GetEnumMembers();

    void SetIndexEnable(int index, bool bEnable);
    bool GetIndexEnable(int index);

    void SetEnumSensitivity(std::vector<int> value);
    std::vector<int> GetEnumSensitivity();

    void SetRadioBoxStyle(RadioBoxLayoutStyle style);
    RadioBoxLayoutStyle radioBoxStyle();

    void SetRadioBoxColumn(int num);
    int RadioBoxColumn();

public:
    bool eventFilter(QObject* watched, QEvent* event);
signals:
    void EnumerationIndexChanged();
public slots:
    void ComboxTextChanged(const QString text);
    void RadioBoxButtonChecked(int ID);
    void PullDownItemChecked(QAction* action);
public://回调
    CallBack1 m_pEnumerationIndexChanged = nullptr;

    void SetCallBackFun_ComboxTextChanged(CallBack1 pFun);
    void SetCallBackFun_RadioBoxButtonChecked(CallBack1 pFun);
    void SetCallBackFun_PullDownItemChecked(CallBack1 pFun);

private:
    void AddOptionMenuEnum();
    void AddRadioBoxEnum();
    void AddPullDownEnum();
private:
    //OptionMenu
    QComboBox* m_pCombox;
    QHBoxLayout* m_pHLayout;

    //RadioBox
    QWidget* m_pTopWidget;
    QWidget* m_pButtomWidget;
    QVBoxLayout* m_pVLayout;
    QButtonGroup* m_pButtonGroup;
    QGridLayout* m_pGridLayout;

    //PullDown
    QPushButton* m_pPullButton;
    QActionGroup* m_pActionGroup;
private:
    int i_CurIndex;
    EnumerationStyle m_Style;
    bool b_LabelVisible;

    QStringList m_Icons;
    QStringList m_EnumMembers;
    std::vector<int> m_EnumSensitivity;

    RadioBoxLayoutStyle m_RadioStyle;
    int i_Columns;
};

#endif // DEBLOCKENUMERATION_H
