#ifndef DEBLOCKTREE_H
#define DEBLOCKTREE_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include "DECommon.h"

class DEBlockTree : public QWidget
{
    Q_OBJECT
public:
    DEBlockTree(QWidget* parent = nullptr);

    void InitTree();
    QStandardItem* CreateItem(QIcon icon, QString name);

public slots:
    void onTreeClicked(const QModelIndex &index);
    void onTreeDoubleClicked(const QModelIndex &index);

signals:
    void AddBlock(QString type);

private:
    QTreeView* m_TreeView;
    QStandardItemModel* m_TreeModel;
};

#endif // DEBLOCKTREE_H
