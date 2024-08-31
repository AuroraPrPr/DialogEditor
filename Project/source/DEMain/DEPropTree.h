#ifndef DEPROPTREE_H
#define DEPROPTREE_H

#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include "DEDelegate.h"

enum PropType
{
    PropString,
    PropInt,
    PropDouble,
    PropBool,
    PropEnumerationStyle,
    PropRadioBoxStyle,
    PropPresentationStyle,
    PropStepStatus,
    PropSelectMode,
};

class DEPropTree: public QWidget
{
    Q_OBJECT
public:
    DEPropTree(QWidget* parent = nullptr);

public:
    void Init();
    void PropTreeItemInit();
    void ReadXmlAndShowBlockProp(QString BlockID);
    inline QString GetCurEditBlockID() {return s_BlockID;};
    void Clear();

public:
    void AddGeneralProp(QString text);
    void AddSpecialProp(QString name, QString value, PropType type = PropString);

public slots:
    void OnCloseEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    void OnTableEditingFinished();
    void OnComboxTextChange(QString text);

private:
    QTableView* m_Table;
    QStandardItemModel* m_Model;

    QStandardItem* m_General;
    QStandardItem* m_Special;

    ReadOnlyDelegate* readOnlyDelegate;
    IntDelegate* intDelegate;
    DoubleDelegate* doubleDelegate;

    ComboxDelegate* boolDelegate;
    ComboxDelegate* enumerationStyleDelegate;
    ComboxDelegate* radioBoxStyleDelegate;
    ComboxDelegate* presentationStyleDelegate;
    ComboxDelegate* stepStatusDelegate;
    ComboxDelegate* selectModeDelegate;
private:
    QString s_BlockID = "DEDialog";
signals:
    void PropChanged(bool bDialogTreeRefresh = false);
};

class PropHHeader : public QHeaderView
{
public:
    explicit PropHHeader(QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

#endif // DEPROPTREE_H
