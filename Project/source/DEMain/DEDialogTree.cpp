#include "DEDialogTree.h"
#include <QStandardItem>
#include <QBoxLayout>
#include <QMouseEvent>

#include "DERoot.h"
#include "DEPartCollection.h"
#include "DEPart.h"
#include <QDebug>

DEDialogTree::DEDialogTree(QWidget* parent) : QWidget(parent)
{
    setMinimumWidth(200);
    readOnlyDelegate = new ReadOnlyDelegate(this);

    InitTree();

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_Tree);
    setLayout(layout);

    connect(m_Tree, &QTreeView::clicked, this, &DEDialogTree::onTreeClicked);
    connect(m_Tree, &QTreeView::doubleClicked, this, &DEDialogTree::onTreeDoubleClicked);
}

void DEDialogTree::InitTree()
{
    m_Tree = new DETreeTable(this);

    QStringList headers;
    headers << tr("名称") << tr("文本") << tr("类型") << tr("备注");
    m_Tree->SetHeaders(headers);

    QStringList root;
    root << tr("DEDialog");
    m_Tree->AppendRow(root);
    m_Tree->setItemDelegateForRow(0, readOnlyDelegate);

    m_Tree->setModel(m_Tree->m_TreeModel);

    m_Tree->setColumnWidth(0, 200);
    m_Tree->setColumnWidth(1, 200);
    m_Tree->setColumnWidth(2, 200);
}

void DEDialogTree::ReadXmlAndShow(QString BlockID)
{
    m_Tree->Clear();

    DERoot *root = DERoot::GetDERoot();
    DEPart* part = root->GetPartCollection()->GetCurPart();

    QDomDocument* doc = part->GetXml();

    QDomElement Xmlroot = doc->documentElement();
    QStringList rootText;
    rootText << Xmlroot.tagName();
    QStandardItem* rootItem = m_Tree->AppendRow(rootText);
    SearchAllChildAndAdd(Xmlroot, rootItem, BlockID);

    m_Tree->expandAll();
}

void DEDialogTree::SearchAllChildAndAdd(QDomElement parent, QStandardItem* parentItem, QString BlockID)
{
    QDomNodeList list = parent.childNodes();
    if(list.isEmpty())
        return;

    for(int i=0; i<list.size(); i++)
    {
        QDomElement e = list.at(i).toElement();
        QStringList rowText;
        rowText << e.tagName()
                << e.attribute("Label")
                << e.attribute("Type")
                << e.attribute("Note");
        QStandardItem* item = m_Tree->AppendRow(parentItem, rowText);
        if(BlockID == rowText[0])
        {
            m_Tree->setCurrentIndex(item->index());
        }
        if(e.hasChildNodes())
        {
            SearchAllChildAndAdd(e, item, BlockID);
        }
    }
}

void DEDialogTree::AddNewChild(QStringList list)
{
    QModelIndex editedIndex = m_Tree->currentIndex();
    QString BlockID;
    QStandardItem *curSelectItem, *parentItem;

    if (editedIndex.isValid())
    {
        QModelIndex selected = editedIndex.sibling(editedIndex.row(), 0);
        BlockID = m_Tree->m_TreeModel->itemData(selected).values()[0].toString();
        curSelectItem = m_Tree->m_TreeModel->itemFromIndex(selected);
    }
    else
    {
        //默认为根节点
        BlockID = "DEDialog";
    }

    
    if(BlockID == "DEDialog")
    {
        parentItem = m_Tree->m_TreeModel->findItems("DEDialog")[0];
    }
    else
    {
        QModelIndex TypeIndex = editedIndex.sibling(editedIndex.row(), 2);
        QString type = m_Tree->m_TreeModel->itemFromIndex(TypeIndex)->text();
        if(type == "Group")
        {
            parentItem = curSelectItem;
        }
        else
        {
            parentItem = curSelectItem->parent();
        }
    }

    QStandardItem* item = m_Tree->AppendRow(parentItem, list);
    m_Tree->setCurrentIndex(item->index());
    emit CurUIBlockChanged(list[0]);
}

QString DEDialogTree::GetCurBlockID()
{
    QModelIndex editedIndex = m_Tree->currentIndex();
    QString BlockID;

    if (editedIndex.isValid())
    {
        QModelIndex selected = editedIndex.sibling(editedIndex.row(), 0);
        BlockID = m_Tree->m_TreeModel->itemData(selected).values()[0].toString();
    }
    else
    {
        //默认为根节点
        BlockID = "DEDialog";
    }

    return BlockID;
}

void DEDialogTree::onTreeClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    QModelIndex selected = index.sibling(index.row(), 0);
    QString BlockID(m_Tree->m_TreeModel->itemData(selected).values()[0].toString());

    emit CurUIBlockChanged(BlockID);
}
void DEDialogTree::onTreeDoubleClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    QModelIndex selected = index.sibling(index.row(), 0);
    QString BlockID(m_Tree->m_TreeModel->itemData(selected).values()[0].toString());

    emit CurUIBlockChanged(BlockID);
}
