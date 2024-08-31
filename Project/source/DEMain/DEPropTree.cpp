#include "DEPropTree.h"
#include <QStandardItem>
#include <QBoxLayout>
#include <QMouseEvent>

#include "DERoot.h"
#include "DEPartCollection.h"
#include "DEPart.h"
#include <QDebug>

#include "DEBlockAngularDimension.h"
#include "DEBlockDimension.h"
#include "DEBlockDouble.h"
#include "DEBlockEnumeration.h"
#include "DEBlockGroup.h"
#include "DEBlockInt.h"
#include "DEBlockLabel.h"
#include "DEBlockLinearDimension.h"
#include "DEBlockObject.h"
#include "DEBlockRadiusDimension.h"
#include "DEBlockToggle.h"

DEPropTree::DEPropTree(QWidget* parent) : QWidget(parent)
{
    setMinimumWidth(200);

    readOnlyDelegate = new ReadOnlyDelegate(this);
    intDelegate = new IntDelegate(this);
    doubleDelegate = new DoubleDelegate(this);

    QList<QString> boollist, enumerationStyle, radioBoxStyle, presentationStyle, stepStatus, selectMode;
    boollist << "True" << "False";
    boolDelegate = new ComboxDelegate(boollist, this);
    enumerationStyle << "OptionMenu" << "RadioBox" << "PullDown";
    enumerationStyleDelegate = new ComboxDelegate(enumerationStyle, this);
    radioBoxStyle << "vertical" << "horizontal";
    radioBoxStyleDelegate = new ComboxDelegate(radioBoxStyle, this);
    presentationStyle << "Keyin" << "Spin";
    presentationStyleDelegate = new ComboxDelegate(presentationStyle, this);
    stepStatus << "Required" << "Optional" << "SatisFied";
    stepStatusDelegate = new ComboxDelegate(stepStatus, this);
    selectMode << "Single" << "Multiple";
    selectModeDelegate = new ComboxDelegate(selectMode, this);

    Init();

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_Table);
    setLayout(layout);

    //编辑完成信号
    connect(m_Table->itemDelegate(), &QAbstractItemDelegate::closeEditor,
            this, &DEPropTree::OnCloseEditor);
    connect(intDelegate, &DEDelegate::editingFinished, this, &DEPropTree::OnTableEditingFinished);
    connect(doubleDelegate, &DEDelegate::editingFinished, this, &DEPropTree::OnTableEditingFinished);
    connect(boolDelegate, &DEDelegate::comboxTextChanged, this, &DEPropTree::OnComboxTextChange);
    connect(readOnlyDelegate, &DEDelegate::comboxTextChanged, this, &DEPropTree::OnComboxTextChange);
    connect(enumerationStyleDelegate, &DEDelegate::comboxTextChanged, this, &DEPropTree::OnComboxTextChange);
    connect(radioBoxStyleDelegate, &DEDelegate::comboxTextChanged, this, &DEPropTree::OnComboxTextChange);
    connect(presentationStyleDelegate, &DEDelegate::comboxTextChanged, this, &DEPropTree::OnComboxTextChange);
    connect(stepStatusDelegate, &DEDelegate::comboxTextChanged, this, &DEPropTree::OnComboxTextChange);
    connect(selectModeDelegate, &DEDelegate::comboxTextChanged, this, &DEPropTree::OnComboxTextChange);
}

void DEPropTree::Init()
{
    m_Table = new QTableView(this);
    PropHHeader* header = new PropHHeader(m_Table);
    m_Table->setHorizontalHeader(header);
    m_Model = new QStandardItemModel(this);
    m_Table->setModel(m_Model);

    QStringList headers;
    headers << tr("属性") << tr("值");
    m_Model->setHorizontalHeaderLabels(headers);

    m_Table->verticalHeader()->setVisible(false);
    m_Table->verticalHeader()->setDefaultSectionSize(15);
    m_Table->setColumnWidth(0, 300);
}

void DEPropTree::PropTreeItemInit()
{
    //常规
    m_General = new QStandardItem("常规");
    m_General->setEditable(false);
    m_Model->appendRow(m_General);

    AddGeneralProp("BlockID");
    AddGeneralProp("Enable");
    AddGeneralProp("Group");
    AddGeneralProp("Label");
    AddGeneralProp("Show");

    //特定于块
    m_Special = new QStandardItem("独特");
    m_Special->setEditable(false);
    m_Model->appendRow(m_Special);

    m_Table->setItemDelegateForRow(0, readOnlyDelegate);
    m_Table->setItemDelegateForRow(2, boolDelegate);
    m_Table->setItemDelegateForRow(3, boolDelegate);
    m_Table->setItemDelegateForRow(5, boolDelegate);
    m_Table->setItemDelegateForRow(6, readOnlyDelegate);
}


void DEPropTree::AddGeneralProp(QString text)
{
    QStandardItem* item = new QStandardItem(text);
    item->setEditable(false);
    m_Model->appendRow(item);
}

void DEPropTree::AddSpecialProp(QString name, QString value, PropType type)
{
    QStandardItem* PropItem = new QStandardItem(name);
    PropItem->setEditable(false);
    QStandardItem* ValueItem = new QStandardItem(value);
    QList<QStandardItem*> list;
    list << PropItem << ValueItem;
    m_Model->appendRow(list);

    int currow = m_Model->rowCount() -1;
    switch(type)
    {
    case PropString:
        break;
    case PropInt:
        m_Table->setItemDelegateForRow(currow, intDelegate);
        break;
    case PropDouble:
        m_Table->setItemDelegateForRow(currow, doubleDelegate);
        break;
    case PropBool:
        m_Table->setItemDelegateForRow(currow, boolDelegate);
        break;
    case PropEnumerationStyle:
        m_Table->setItemDelegateForRow(currow, enumerationStyleDelegate);
        break;
    case PropRadioBoxStyle:
        m_Table->setItemDelegateForRow(currow, radioBoxStyleDelegate);
        break;
    case PropPresentationStyle:
        m_Table->setItemDelegateForRow(currow, presentationStyleDelegate);
        break;
    case PropStepStatus:
        m_Table->setItemDelegateForRow(currow, stepStatusDelegate);
        break;
    case PropSelectMode:
        m_Table->setItemDelegateForRow(currow, selectModeDelegate);
        break;
    default:
        break;
    }
}

void DEPropTree::ReadXmlAndShowBlockProp(QString BlockID)
{
    m_Model->removeRows(0, m_Model->rowCount());

    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();
    if(BlockID == "DEDialog")
        return;

    QDomNodeList list = doc->documentElement().elementsByTagName(BlockID);
    if(list.isEmpty())
        return;

    PropTreeItemInit();
    s_BlockID = BlockID;

    //理论上只有一个
    QDomElement element = list.at(0).toElement();

    QString type = element.attribute("Type");

    ///*
    //General
    QStandardItem* item1 = new QStandardItem(element.tagName());
    m_Model->setItem(1, 1, item1);

    QStandardItem* item2 = new QStandardItem(element.attribute("Enable"));
    m_Model->setItem(2, 1, item2);

    QStandardItem* item3 = new QStandardItem(element.attribute("Group"));
    m_Model->setItem(3, 1, item3);

    QStandardItem* item4 = new QStandardItem(element.attribute("Label"));
    m_Model->setItem(4, 1, item4);

    QStandardItem* item5 = new QStandardItem(element.attribute("Show"));
    m_Model->setItem(5, 1, item5);

    //Special
    QMap<QString, QString> temp;//仅用于排序
    QDomNamedNodeMap map = element.attributes();
    for(int i = 0; i<map.size(); i++)
    {
        QDomAttr prop = map.item(i).toAttr();
        QString name = prop.name();

        if(name != "Enable"
                && name != "Group"
                && name != "Label"
                && name != "Show")
        {
            temp.insert(name, prop.value());
        }
    }

    if(!temp.isEmpty())
    {
        for(auto it = temp.begin(); it != temp.end(); it++)
        {
            QString name = it.key();
            QString value = it.value();

            if(name == "EnumerationStyle")
            {
                AddSpecialProp(name, value, PropEnumerationStyle);
            }
            else if(name == "Index" || name == "Column")
            {
                AddSpecialProp(name, value, PropInt);
            }
            else if(name == "LabelVisibility" || name == "ReadOnly" || name == "Expanded")
            {
                AddSpecialProp(name, value, PropBool);
            }
            else if(name == "RadioBoxStyle")
            {
                AddSpecialProp(name, value, PropRadioBoxStyle);
            }
            else if(name == "PresentationStyle")
            {
                AddSpecialProp(name, value, PropPresentationStyle);
            }
            else if(name == "StepStatus")
            {
                AddSpecialProp(name, value, PropStepStatus);
            }
            else if(name == "SelectMode")
            {
                AddSpecialProp(name, value, PropSelectMode);
            }
            else if(name == "Value")
            {
                if(type == "Toggle")
                    AddSpecialProp(name, value, PropBool);
                else if(type == "Integer")
                    AddSpecialProp(name, value, PropInt);
                else
                    AddSpecialProp(name, value, PropDouble);
            }
            else if(name == "Step")
            {
                if(type == "Integer")
                    AddSpecialProp(name, value, PropInt);
                else
                    AddSpecialProp(name, value, PropDouble);
            }
            else if(name == "EnumMembers")
            {
                AddSpecialProp(name, value);
            }
        }
    }

    m_Table->setModel(m_Model);
}

void DEPropTree::OnCloseEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)
{
    QModelIndex editedIndex = m_Table->currentIndex();
    int row = editedIndex.row();
    QModelIndex NameIndex = m_Model->index(row, 0);
    QModelIndex ValueIndex = m_Model->index(row, 1);
    QString name = m_Model->itemFromIndex(NameIndex)->text();
    QString value = m_Model->itemFromIndex(ValueIndex)->text();

    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();

    QDomNodeList list = doc->documentElement().elementsByTagName(s_BlockID);
    QDomElement element = list.at(0).toElement();

    if(name == "BlockID")
    {
        QString preText = element.tagName();
        if(value == preText)//如果相同,跳过
            return;

        element.setTagName(value);
        s_BlockID = value;
    }
    else
    {
        QString preText = element.attribute(name);
        if(value == preText)//如果相同,跳过
            return;

        element.setAttribute(name, value);
    }

    if(name == "BlockID" || name == "Label")
    {
        emit PropChanged(true);
    }
    else
    {
        emit PropChanged();
    }
}

void DEPropTree::OnTableEditingFinished()
{
    QModelIndex editedIndex = m_Table->currentIndex();
    int row = editedIndex.row();
    QModelIndex NameIndex = m_Model->index(row, 0);
    QModelIndex ValueIndex = m_Model->index(row, 1);
    QString name = m_Model->itemFromIndex(NameIndex)->text();
    QString value = m_Model->itemFromIndex(ValueIndex)->text();

    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();

    QDomNodeList list = doc->documentElement().elementsByTagName(s_BlockID);
    QDomElement element = list.at(0).toElement();
    QString preText = element.attribute(name);

    if(value == preText)//如果相同,跳过
        return;

    element.setAttribute(name, value);
    emit PropChanged();
}

void DEPropTree::OnComboxTextChange(QString text)
{
    QModelIndex editedIndex = m_Table->currentIndex();
    int row = editedIndex.row();
    QModelIndex NameIndex = m_Model->index(row, 0);
    QModelIndex ValueIndex = m_Model->index(row, 1);
    QString name = m_Model->itemFromIndex(NameIndex)->text();
    QString value = m_Model->itemFromIndex(ValueIndex)->text();

    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();

    QDomNodeList list = doc->documentElement().elementsByTagName(s_BlockID);
    QDomElement element = list.at(0).toElement();
    QString preText = element.attribute(name);

    if(text == preText)//如果相同,跳过
        return;

    element.setAttribute(name, text);
    emit PropChanged();
}

void DEPropTree::Clear()
{
    m_Model->removeRows(0, m_Model->rowCount());
}



PropHHeader::PropHHeader(QWidget *parent) : QHeaderView(Qt::Horizontal, parent)
{
    setStyleSheet("QHeaderView::section{"
                  "border-top:0px solid #E5E5E5;"
                  "border-left:0px solid #E5E5E5;"
                  "border-right:0.5px solid #E5E5E5;"
                  "border-bottom: 0.5px solid #E5E5E5;"
                  "background-color:lightgray;"
                  "padding:4px;"
                  "}");
    setDefaultAlignment(Qt::AlignLeft);
    setStretchLastSection(true);
}

QSize PropHHeader::sizeHint() const
{
    QSize baseSize = QHeaderView::sizeHint();
    baseSize.setHeight( 25 );
    return baseSize;
}
