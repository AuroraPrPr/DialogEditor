#include "DETreeTable.h"
#include <QHeaderView>
#include <QPen>
#include <QPainter>

DETreeTable::DETreeTable(QWidget *parent) : QTreeView(parent)
{
    /*
     * 说明：
     * 采用设置样式表和重写绘制行函数来实现表格树
     * 绘制行drawRow：用于绘制表格线。这样便不用考虑给branch、item和adjoins-item绘制上下边界线
     * 设置样式表：包括设置树、设置item的右侧线、设置选择样式、添加图片
     * 其中树节点关联线通过给adjoins-item的边框添加背景图片实现
     * Qt样例：https://doc.qt.io/qt-5/stylesheet-examples.html#customizing-qtreeview
     *
     * Qt自带有Windows样式：setStyle(QStyleFactory::create("windows"));
    */

    //设置样式表
    QString style =
            R"(
            QTreeView {
                show-decoration-selected: 1;
                alternate-background-color: lightgray;
                outline: none;
            }

            QTreeView::item {
                border: 1px solid #d9d9d9;
                border-left: transparent;
                border-top: transparent;
                border-bottom: transparent;
            }

            QTreeView::item:selected,
            QTreeView::branch:selected
            {
                background: lightblue;
            }

            QTreeView::branch:has-siblings:!adjoins-item {
                border-image: url(:/res/Treeview/vline.png) 0;
            }

            QTreeView::branch:has-siblings:adjoins-item {
                border-image: url(:/Icon/Icon/TreeTable/branch-more.png) 0;
            }

            QTreeView::branch:!has-children:!has-siblings:adjoins-item {
                border-image: url(:/Icon/Icon/TreeTable/branch-end.png) 0;
            }

            QTreeView::branch:has-children:!has-siblings:closed,
            QTreeView::branch:closed:has-children:has-siblings {
                    border-image: none;
                    image: url(:/Icon/Icon/TreeTable/branch-closed.png);
            }

            QTreeView::branch:open:has-children:!has-siblings,
            QTreeView::branch:open:has-children:has-siblings  {
                    border-image: none;
                    image: url(:/Icon/Icon/TreeTable/branch-open.png);
            }
            )";
    setStyleSheet(style);
    setAlternatingRowColors(true); // 隔行变色

    header()->setStyleSheet(QString(R"(
                                    QHeaderView::section{
                                        border: 1px solid #d9d9d9;
                                        border-left: transparent;
                                        border-top: transparent;
                                        background-color: lightgray;
                                    }
                                    )"));
    m_TreeModel = new QStandardItemModel(this);
}

void DETreeTable::drawRow(QPainter * painter, const QStyleOptionViewItem & options, const QModelIndex & index) const
{
    QTreeView::drawRow(painter, options, index);

    //绘制网格线
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(217, 217, 217));

    painter->save();
    painter->setPen(pen);
    painter->drawRect(options.rect);
    painter->restore();
}

//注：这样设置可以使TreeView选择效果和表格一样
//QTreeView {
//    show-decoration-selected: 1;
//}

//QTreeView::item:selected,
//QTreeView::branch:selected
//{
//    background: lightblue;
//}

void DETreeTable::SetHeaders(QStringList headers)
{
    if(!m_TreeModel)
        return;

    m_TreeModel->setHorizontalHeaderLabels(headers);
}

void DETreeTable::Clear()
{
    if(!m_TreeModel)
        return;

    m_TreeModel->removeRows(0, m_TreeModel->rowCount());
}

QStandardItem* DETreeTable::AppendRow(QStringList texts)
{
    if(!m_TreeModel)
        return nullptr;

    QList<QStandardItem*> list;
    QStandardItem* item0;
    for(int i=0; i<texts.size(); i++)
    {
        QStandardItem* item = new QStandardItem(texts[i]);
        item->setEditable(false);

        list << item;
        if(i == 0)
            item0 = item;
    }

    m_TreeModel->appendRow(list);
    return item0;
}

QStandardItem* DETreeTable::AppendRow(QStandardItem* parent, QStringList texts)
{
    if(!parent || !m_TreeModel)
        return nullptr;

    QList<QStandardItem*> list;
    QStandardItem* item0;
    for(int i=0; i<texts.size(); i++)
    {
        QStandardItem* item = new QStandardItem(texts[i]);
        item->setEditable(false);

        list << item;
        if(i == 0)
            item0 = item;
    }

    parent->appendRow(list);
    return item0;
}

void DETreeTable::AppendRow(QModelIndex index, QStringList texts)
{
    int row = index.row();
    QModelIndex Index = m_TreeModel->index(row, 0);
    QStandardItem* item = m_TreeModel->itemFromIndex(Index);
    AppendRow(item, texts);
}
