#ifndef DEDIALOGTREE_H
#define DEDIALOGTREE_H

#include <DETreeTable.h>
#include <QStandardItemModel>
#include <QDomDocument>
#include "DEDelegate.h"

class DEDialogTree : public QWidget
{
    Q_OBJECT
public:
    DEDialogTree(QWidget* parent = nullptr);

    void InitTree();

public:
    void ReadXmlAndShow(QString BlockID = "DEDialog");
    void SearchAllChildAndAdd(QDomElement parent, QStandardItem* parentItem, QString BlockID);
    void AddNewChild(QStringList list);

    QString GetCurBlockID();
public slots:
    void onTreeClicked(const QModelIndex &index);
    void onTreeDoubleClicked(const QModelIndex &index);

signals:
    void CurUIBlockChanged(QString BlockID);

private:
    DETreeTable* m_Tree;
    ReadOnlyDelegate* readOnlyDelegate;
};

#endif // DEDIALOGTREE_H
