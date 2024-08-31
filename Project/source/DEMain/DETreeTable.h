#ifndef DETREETABLE_H
#define DETREETABLE_H

#include <QTreeView>
#include <QStandardItemModel>
#include "DECommon.h"

class DETreeTable : public QTreeView
{
public:
    DETreeTable(QWidget *parent = nullptr);

    virtual void drawRow(QPainter *painter, const QStyleOptionViewItem &options,
                         const QModelIndex &index) const override;

public:
    void SetHeaders(QStringList headers);
    void Clear();
    QStandardItem* AppendRow(QStringList texts);
    QStandardItem* AppendRow(QStandardItem* parent, QStringList texts);
    void AppendRow(QModelIndex index, QStringList texts);
public:
    QStandardItemModel* m_TreeModel;
};

#endif // DETREETABLE_H
