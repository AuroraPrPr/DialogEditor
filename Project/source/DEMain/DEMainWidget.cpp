#include "DEMainWidget.h"
#include <QBoxLayout>

#include "DERoot.h"
#include "DEPartCollection.h"
#include "DEPart.h"

#include "DEDialog.h"
#include "DEBlockCommon.h"
#include <QDebug>

DEMainWidget::DEMainWidget(QWidget* parent) : QWidget(parent)
{
    m_pDlg = new DEDialog(this);

    m_BlockTree = new DEBlockTree(this);
    m_DialogTree = new DEDialogTree(this);
    m_PropTree = new DEPropTree(this);

    QWidget* right = new QWidget(this);
    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->setSpacing(5);
    vlayout->setContentsMargins(0, 0, 0, 0);

    vlayout->addWidget(m_DialogTree);
    vlayout->addWidget(m_PropTree);
    right->setLayout(vlayout);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSpacing(5);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(m_BlockTree);
    layout->addWidget(right);
    setLayout(layout);

    connect(m_BlockTree, &DEBlockTree::AddBlock, this, &DEMainWidget::AddBlock);
    connect(m_pDlg, &DEDialog::DialogClosed, this, &DEMainWidget::DialogClosed);
    connect(m_DialogTree, &DEDialogTree::CurUIBlockChanged, this, &DEMainWidget::RefreshPropTree);
    connect(m_PropTree, &DEPropTree::PropChanged, this, &DEMainWidget::BlockPropChanged);
}

void DEMainWidget::DialogClosed()
{
    m_pDlg = new DEDialog(this);
    connect(m_pDlg, &DEDialog::DialogClosed, this, &DEMainWidget::DialogClosed);
    DialogRefresh();
}

void DEMainWidget::Close()
{
    if(m_pDlg)
    {
        disconnect(m_pDlg, &DEDialog::DialogClosed, this, &DEMainWidget::DialogClosed);
    }
}

void DEMainWidget::Refresh(QString BlockID)
{
    m_DialogTree->ReadXmlAndShow(BlockID);
    DialogRefresh();
}

void DEMainWidget::DialogClose()
{
    Close();
    if(m_pDlg)
    {
        m_pDlg->hide();
        delete m_pDlg;
        m_pDlg = nullptr;
    }
}

void DEMainWidget::AddBlock(QString type)
{
    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();

    QString curBlockID = m_DialogTree->GetCurBlockID();
    QDomElement element;
    if(curBlockID == "DEDialog")
    {
        element = doc->documentElement();
    }
    else
    {
        QDomNodeList list = doc->documentElement().elementsByTagName(curBlockID);
        QDomElement e = list.at(0).toElement();

        if (e.attribute("Type") != "Group")
        {
            element = e.parentNode().toElement();
        }
        else
        {
            element = e;
        }
    }

    QDomElement e = CreateBlockElement(type);
    element.appendChild(e);
    root->GetPartCollection()->GetCurPart()->SetSaved(false);

    QStringList rowText;
    rowText << e.tagName()
            << e.attribute("Label")
            << e.attribute("Type")
            << e.attribute("Note");
    m_DialogTree->AddNewChild(rowText);
    //刷新对话框
    DialogRefresh();
}

QDomElement DEMainWidget::CreateBlockElement(QString LabelType)
{
    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();

    QString type = GetTypeFromBlockTree(LabelType);
    QString name = root->GetPartCollection()->GetCurPart()->GetAutoBlockID(type);
    QDomElement e = doc->createElement(name);

    //General
    e.setAttribute("Type", type);
    e.setAttribute("Enable", "True");
    e.setAttribute("Group", "False");
    e.setAttribute("Label", "无标题");
    e.setAttribute("Show", "True");

    //Special
    if(type == "Label")
    {

    }
    else if(type == "Enumeration")
    {
        e.setAttribute("EnumerationStyle", "OptionMenu");
        e.setAttribute("Index", 0);
        e.setAttribute("LabelVisibility", "True");
        e.setAttribute("EnumMembers", "");
        e.setAttribute("RadioBoxStyle", "vertical");
        e.setAttribute("Column", 0);
    }
    else if(type == "Toggle")
    {
        e.setAttribute("Value", "False");
    }
    else if(type == "Integer")
    {
        e.setAttribute("PresentationStyle", "Keyin");
        e.setAttribute("Value", 0);
        e.setAttribute("LabelVisibility", "True");
        e.setAttribute("ReadOnly", "False");
        e.setAttribute("Step", 1);
    }
    else if(type == "Double")
    {
        e.setAttribute("PresentationStyle", "Keyin");
        e.setAttribute("Value", 0.0);
        e.setAttribute("LabelVisibility", "True");
        e.setAttribute("ReadOnly", "False");
        e.setAttribute("Step", 1.0);
    }
    else if(type == "LinearDimension")
    {
        e.setAttribute("Value", 0.0);
    }
    else if(type == "AngularDimension")
    {
        e.setAttribute("Value", 0.0);
    }
    else if(type == "RadiusDimension")
    {
        e.setAttribute("Value", 0.0);
    }
    else if(type == "Group")
    {
        e.setAttribute("Expanded", "True");
    }
    else if(type == "SelectObject")
    {
        e.setAttribute("StepStatus", "Required");
        e.setAttribute("SelectMode", "Single");
    }
    return e;
}

void DEMainWidget::DialogRefresh()
{
    if (m_pDlg)
    {
        delete m_pDlg;
        m_pDlg = new DEDialog(this);
        connect(m_pDlg, &DEDialog::DialogClosed, this, &DEMainWidget::DialogClosed);
    }

    DERoot *root = DERoot::GetDERoot();
    DEPart* part = root->GetPartCollection()->GetCurPart();

    QDomDocument* doc = part->GetXml();
    QDomElement Dialog = doc->documentElement();
    QDomNodeList list = Dialog.childNodes();
    if(list.size() <= 0)
        return;

    for(int i=0; i<list.size(); i++)
    {
        QDomElement e = list.at(i).toElement();
        DEBlock* pBlock = CreateBlockFromElement(m_pDlg, e);
        AddBlockToContainer(m_pDlg->m_pBlockContainer, pBlock);

        AddChildBlockToBlock(m_pDlg, e, pBlock);
    }

    m_pDlg->AllBlockInit();
    m_pDlg->show();
    m_pDlg->move(100, 100);
}

void DEMainWidget::AddChildBlockToBlock(DEDialog* pDlg, QDomElement parent, DEBlock* parentBlock)
{
    QDomNodeList list = parent.childNodes();
    if(list.size() <= 0)
        return;

    for(int i=0; i<list.size(); i++)
    {
        QDomElement e = list.at(i).toElement();
        DEBlock* pBlock = CreateBlockFromElement(pDlg, e);
        AddBlockToLayout(pDlg->m_pBlockContainer, (DEBlockLayoutBase*)parentBlock, pBlock);

        AddChildBlockToBlock(pDlg, e, pBlock);
    }
}

DEBlock* DEMainWidget::CreateBlockFromElement(DEDialog* pDlg, QDomElement e)
{
    QString blockID = e.tagName();
    QString type = e.attribute("Type");
    QString label = e.attribute("Label");
    DEBlock* pBlock = nullptr;
    //基本
    if(type == "Label")
    {
        pBlock = new DEBlockLabel(pDlg, blockID, label);
    }
    else if(type == "Enumeration")
    {
        DEBlockEnumeration* Block = new DEBlockEnumeration(pDlg, blockID, label);

        QString stylestr = e.attribute("EnumerationStyle");
        EnumerationStyle style = OptionMenu;
        if(stylestr == "RadioBox") style = RadioBox;
        else if(stylestr == "PullDown") style = PullDown;
        Block->SetEnumerationStyle(style);

        Block->SetCurIndex(e.attribute("Index").toInt());
        Block->SetRadioBoxColumn(e.attribute("Column").toInt());

        bool bLabelVisibility = true;
        if(e.attribute("LabelVisibility") == "False")
            bLabelVisibility = false;
        Block->SetLabelVisibility(bLabelVisibility);

        RadioBoxLayoutStyle rstyle = vertical;
        if(e.attribute("RadioBoxStyle") == "horizontal")
            rstyle = horizontal;
        Block->SetRadioBoxStyle(rstyle);

        QStringList members = e.attribute("EnumMembers").split(",");
        Block->SetEnumMembers(members);

        pBlock = Block;
    }
    else if(type == "Toggle")
    {
        DEBlockToggle* Block = new DEBlockToggle(pDlg, blockID, label);

        bool bCheck = false;
        if(e.attribute("Value") == "True")
            bCheck = true;
        Block->SetValue(bCheck);

        pBlock = Block;
    }
    else if(type == "Integer")
    {
        DEBlockInt* Block = new DEBlockInt(pDlg, blockID, label);

        PresentationStyle style = Keyin;
        if(e.attribute("PresentationStyle") == "Spin")
            style = Spin;
        Block->SetPresentationStyle(style);

        Block->SetValue(e.attribute("Value").toInt());
        Block->SetStep(e.attribute("Step").toInt());

        bool bLabelVisibility = true;
        if(e.attribute("LabelVisibility") == "False")
            bLabelVisibility = false;
        Block->SetLabelVisibility(bLabelVisibility);

        bool bReadOnly = false;
        if(e.attribute("ReadOnly") == "True")
            bReadOnly = true;
        Block->SetReadOnly(bReadOnly);

        pBlock = Block;
    }
    else if(type == "Double")
    {
        DEBlockDouble* Block = new DEBlockDouble(pDlg, blockID, label);

        PresentationStyle style = Keyin;
        if(e.attribute("PresentationStyle") == "Spin")
            style = Spin;
        Block->SetPresentationStyle(style);

        Block->SetValue(e.attribute("Value").toDouble());
        Block->SetStep(e.attribute("Step").toDouble());

        bool bLabelVisibility = true;
        if(e.attribute("LabelVisibility") == "False")
            bLabelVisibility = false;
        Block->SetLabelVisibility(bLabelVisibility);

        bool bReadOnly = false;
        if(e.attribute("ReadOnly") == "True")
            bReadOnly = true;
        Block->SetReadOnly(bReadOnly);

        pBlock = Block;
    }
    else if(type == "LinearDimension")
    {
        DEBlockLinearDimension* Block = new DEBlockLinearDimension(pDlg, blockID, label);

        Block->SetValue(e.attribute("Value").toDouble());

        pBlock = Block;
    }
    else if(type == "AngularDimension")
    {
        DEBlockAngularDimension* Block = new DEBlockAngularDimension(pDlg, blockID, label);

        Block->SetValue(e.attribute("Value").toDouble());

        pBlock = Block;
    }
    else if(type == "RadiusDimension")
    {
        DEBlockRadiusDimension* Block = new DEBlockRadiusDimension(pDlg, blockID, label);

        Block->SetValue(e.attribute("Value").toDouble());

        pBlock = Block;
    }
    else if(type == "Group")
    {
        DEBlockGroup* Block = new DEBlockGroup(pDlg, blockID, label);

        bool bExpanded = true;
        if(e.attribute("Expanded") == "False")
            bExpanded = false;
        Block->SetExpanded(bExpanded);

        pBlock = Block;
    }
    else if(type == "SelectObject")
    {
        DEBlockObject* Block = new DEBlockObject(pDlg, blockID, label);

        StepStatus status = Required;
        if(e.attribute("StepStatus") == "Optional")
            status = Optional;
        else if(e.attribute("StepStatus") == "SatisFied")
            status = SatisFied;
        Block->StepStatusChanged(status);

        SelectMode mode = Single;
        if(e.attribute("SelectMode") == "Multiple")
            mode = Multiple;
        Block->SetSelectMode(mode);

        pBlock = Block;
    }

    if(!pBlock)
        return nullptr;

    QString Enable = e.attribute("Enable");
    QString Group = e.attribute("Group");
    QString Show = e.attribute("Show");
    bool bEnable = true, bGroup = false, bShow = true;
    if(Enable == "False") bEnable = false;
    if(Group == "True") bGroup = true;
    if(Show == "False") bShow = false;
    pBlock->SetEnable(bEnable);
    pBlock->SetShow(bShow);
    pBlock->SetGroup(bGroup);
    return pBlock;
}

QString DEMainWidget::GetTypeFromBlockTree(QString LabelType)
{
    if(LabelType == tr("标签"))
    {
        return "Label";
    }
    else if(LabelType == tr("枚举"))
    {
        return "Enumeration";
    }
    else if(LabelType == tr("勾选框"))
    {
        return "Toggle";
    }
    else if(LabelType == tr("整数"))
    {
        return "Integer";
    }
    else if(LabelType == tr("浮点数"))
    {
        return "Double";
    }
    else if(LabelType == tr("距离测量"))
    {
        return "LinearDimension";
    }
    else if(LabelType == tr("角度测量"))
    {
        return "AngularDimension";
    }
    else if(LabelType == tr("半径测量"))
    {
        return "RadiusDimension";
    }
    else if(LabelType == tr("组"))
    {
        return "Group";
    }
    else if(LabelType == tr("例子"))
    {
        return "SelectObject";
    }

    return "";
}

void DEMainWidget::BlockDelete()
{
    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();

    QString curBlockID = m_DialogTree->GetCurBlockID();
    if(curBlockID == "DEDialog")
    {
        return;
    }

    QDomNodeList list = doc->documentElement().elementsByTagName(curBlockID);
    QDomElement e = list.at(0).toElement();
    QDomElement element = e.parentNode().toElement();

    RemoveChild(e);
    element.removeChild(e);

    root->GetPartCollection()->GetCurPart()->SetSaved(false);
    Refresh();
    m_PropTree->Clear();
}

void DEMainWidget::RemoveChild(QDomElement e)
{
    while(e.hasChildNodes())
    {
        QDomElement child = e.childNodes().at(0).toElement();
        RemoveChild(child);
        e.removeChild(child);
    }
}

void DEMainWidget::BlockMoveUp()
{
    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();

    QString curBlockID = m_DialogTree->GetCurBlockID();
    if(curBlockID == "DEDialog")
    {
        return;
    }

    QDomNodeList list = doc->documentElement().elementsByTagName(curBlockID);
    QDomElement e = list.at(0).toElement();
    QDomElement Brother = e.previousSiblingElement();
    if(Brother.isNull())//上面没有节点
        return;

    QDomNode copy = e.cloneNode();
    QDomElement parent = e.parentNode().toElement();
    parent.insertBefore(copy, Brother);
    RemoveChild(e);
    parent.removeChild(e);

    root->GetPartCollection()->GetCurPart()->SetSaved(false);
    Refresh(curBlockID);
}

void DEMainWidget::BlockMoveDown()
{
    DERoot *root = DERoot::GetDERoot();
    QDomDocument* doc = root->GetPartCollection()->GetCurPart()->GetXml();

    QString curBlockID = m_DialogTree->GetCurBlockID();
    if(curBlockID == "DEDialog")
    {
        return;
    }

    QDomNodeList list = doc->documentElement().elementsByTagName(curBlockID);
    QDomElement e = list.at(0).toElement();
    QDomElement Brother = e.nextSiblingElement();
    if(Brother.isNull())//下面没有节点
        return;

    QDomNode copy = e.cloneNode();
    QDomElement parent = e.parentNode().toElement();
    parent.insertAfter(copy, Brother);
    RemoveChild(e);
    parent.removeChild(e);

    root->GetPartCollection()->GetCurPart()->SetSaved(false);
    Refresh(curBlockID);
}

void DEMainWidget::RefreshPropTree(QString BlockID)
{
    m_PropTree->ReadXmlAndShowBlockProp(BlockID);
}

void DEMainWidget::BlockPropChanged(bool bDialogTreeRefresh)
{
    if(bDialogTreeRefresh)
    {
        QString curBlockID = m_DialogTree->GetCurBlockID();
        m_DialogTree->ReadXmlAndShow(curBlockID);
    }
    DialogRefresh();
}
