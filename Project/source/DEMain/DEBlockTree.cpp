#include "DEBlockTree.h"
#include <QStandardItem>
#include <QBoxLayout>
#include <QMouseEvent>
#include <QAbstractItemView>

#include <iostream>

DEBlockTree::DEBlockTree(QWidget* parent) : QWidget(parent)
{
    setFixedWidth(200);

    InitTree();

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_TreeView);
    setLayout(layout);

    connect(m_TreeView, &QAbstractItemView::clicked, this, &DEBlockTree::onTreeClicked);
    connect(m_TreeView, &QAbstractItemView::doubleClicked, this, &DEBlockTree::onTreeDoubleClicked);
}

void DEBlockTree::InitTree()
{
    m_TreeView = new QTreeView(this);
    m_TreeView->setUpdatesEnabled(true);
    m_TreeView->setMouseTracking(true);
    m_TreeView->setFocusPolicy(Qt::NoFocus);
    m_TreeView->setRootIsDecorated(false);

    m_TreeModel = new QStandardItemModel(this);
    m_TreeView->setHeaderHidden(true);
    m_TreeView->setModel(m_TreeModel);

    QIcon icon1 = QIcon(QObject::tr(":/Icon/Icon/OpenedFolder.png"));
    QStandardItem *Basic = CreateItem(icon1, "基本");
    m_TreeModel->appendRow(Basic);

    QStandardItem *Num = CreateItem(icon1, "数字");
    Num->setEditable(false);
    m_TreeModel->appendRow(Num);

    QStandardItem *Group = CreateItem(icon1, "布局");
    m_TreeModel->appendRow(Group);

    QStandardItem *Select = CreateItem(icon1, "选择");
    m_TreeModel->appendRow(Select);

    //基本控件
    QIcon icon2 = QIcon(QObject::tr(":/Icon/Icon/DE.png"));

    QStandardItem *item00 = CreateItem(icon2, "标签");
    Basic->appendRow(item00);

    QStandardItem *item10 = CreateItem(icon2, "枚举");
    Basic->appendRow(item10);

    QStandardItem *item20 = CreateItem(icon2, "勾选框");
    Basic->appendRow(item20);

    //数字控件
    QStandardItem *item01 = CreateItem(icon2, "整数");
    Num->appendRow(item01);

    QStandardItem *item11 = CreateItem(icon2, "浮点数");
    Num->appendRow(item11);

    QStandardItem *item21 = CreateItem(icon2, "距离测量");
    Num->appendRow(item21);

    QStandardItem *item31 = CreateItem(icon2, "角度测量");
    Num->appendRow(item31);

    QStandardItem *item41 = CreateItem(icon2, "半径测量");
    Num->appendRow(item41);

    //布局控件
    QStandardItem *item02 = CreateItem(icon2, "组");
    Group->appendRow(item02);

    //选择控件
    QStandardItem *item03 = CreateItem(icon2, "例子");
    Select->appendRow(item03);

    m_TreeView->expandAll();
//    m_TreeView->setIconSize(QSize(32, 32));
//    m_TreeView->setStyleSheet(QString("QTreeView::item"
//                                      "{"
//                                      "    height: 32px;"
//                                      "    margin: 3px;"
//                                      "};"));
}

QStandardItem* DEBlockTree::CreateItem(QIcon icon, QString name)
{
    QStandardItem* item = new QStandardItem(icon, name);
    item->setEditable(false);

//    QFont f = QFont();
//    f.setFamily(u8"微软雅黑");
//    f.setPixelSize(20);
//    item->setFont(f);

    return item;
}

void DEBlockTree::onTreeClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    QStandardItem* item = m_TreeModel->itemFromIndex(index);
    if(!item)
        return;

    QString text = item->text();
    QVariant varData = item->data();//这里可以进行数据绑定

    QString parentName = index.parent().data().toString();
    if(parentName == "")
    {
        bool bExpand = m_TreeView->isExpanded(index);
        m_TreeView->setExpanded(index, !bExpand);
    }
    else
    {
        emit(AddBlock(text));
    }

}
void DEBlockTree::onTreeDoubleClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    QStandardItem* item = m_TreeModel->itemFromIndex(index);
    if(!item)
        return;

    QString text = item->text();
    QVariant varData = item->data();

    QString parentName = index.parent().data().toString();
    if(parentName == "")
    {
        bool bExpand = m_TreeView->isExpanded(index);
        m_TreeView->setExpanded(index, !bExpand);
    }
    else
    {
        emit(AddBlock(text));
    }
}
