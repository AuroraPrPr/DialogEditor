#include "DEBlockGroup.h"
#include "DEBlockBox.h"
#include "DEBlockContainer.h"
#include <QEvent>

DEBlockGroup::DEBlockGroup(QWidget* parent, QString BlockID, QString Label)
    : DEBlockLayoutBase(parent, BlockID, Label)
{
    m_Bar = new QWidget(this);
    m_BarLayout = new QHBoxLayout(this);
    m_BarLabel = new QLabel(Label, m_Bar);
    m_BarIcon = new QLabel(m_Bar);
    m_pCtrlBox = new DEBlockBox(this);
    m_Layout = new QVBoxLayout(this);

    QFont font;
    font.setFamily(QObject::tr("微软雅黑"));
    font.setFixedPitch(true);
    font.setPointSize(10);
    m_BarLabel->setFont(font);
    m_BarLabel->setAttribute(Qt::WA_StyleSheet);
    m_BarLabel->setStyleSheet("color: rgb(0, 103, 124)");

    SetIcon();
    m_BarIcon->adjustSize();

    m_BarLayout->setSpacing(0);
    m_BarLayout->setContentsMargins(10, 4, 4, 0);

    m_BarLayout->addWidget(m_BarLabel);
    m_BarLayout->addStretch();//加弹簧就不用给Label设置固定宽
    m_BarLayout->addWidget(m_BarIcon);

    m_Bar->setFixedHeight(22);//图标一般是32*32的
    m_Bar->setLayout(m_BarLayout);
    m_Bar->setAttribute(Qt::WA_Hover, true);
    m_Bar->installEventFilter(this);

    m_pCtrlBox->SetBlockBoxMargin(1);

    m_Layout->setSpacing(0);
    m_Layout->setContentsMargins(0, 0, 0, 0);
    m_Layout->addWidget(m_Bar);
    m_Layout->addWidget(m_pCtrlBox);
    m_Layout->addStretch();

    setLayout(m_Layout);

    m_pLabel->setVisible(false);
}

void DEBlockGroup::BlockInitialize()
{
    DEBlockLayoutBase::BlockInitialize();
//    m_BarLayout->addWidget(m_BarLabel);
//    m_BarLayout->addStretch();//加弹簧就不用给Label设置固定宽
//    m_BarLayout->addWidget(m_BarIcon);

//    m_Bar->setFixedHeight(32);//图标一般是32*32的
//    m_Bar->setLayout(m_BarLayout);
//    m_Bar->setAttribute(Qt::WA_Hover, true);
//    m_Bar->installEventFilter(this);

//    m_pCtrlBox->SetBlockBoxMargin(1);

//    m_Layout->setSpacing(0);
//    m_Layout->setContentsMargins(0, 0, 0, 0);
//    m_Layout->addWidget(m_Bar);
//    m_Layout->addWidget(m_pCtrlBox);

//    m_pWidget->setLayout(m_Layout);
}

QString DEBlockGroup::Type()
{
    return "Group";
}

void DEBlockGroup::SetIcon()
{
    QPixmap pixmap(b_Expanded ? ":/Icon/Icon/Top.png" : ":/Icon/Icon/Bottom.png");
    m_BarIcon->setPixmap(pixmap);
}

void DEBlockGroup::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    if(m_Bar->geometry().contains(point))
    {
        stateSwitch();
    }
    QWidget::mousePressEvent(event);
}

void DEBlockGroup::stateSwitch()
{
    b_Expanded = !b_Expanded;
    SetIcon();

    m_pCtrlBox->setVisible(b_Expanded);
    adjustSize();

    DEBlockLayoutBase* layout = (DEBlockLayoutBase*)this->GetParentLayout();
    while(layout)
    {
        DEBlockLayoutBase* ParentLayout = (DEBlockLayoutBase*)layout->GetParentLayout();
        ParentLayout->GetBlockBox()->adjustSize();
        ParentLayout->adjustSize();
        layout = ParentLayout;
    }

    if(m_pContainer)
    {
        m_pContainer->AdjustCtrlBoxSize();
        m_pContainer->ResizeContainerAndDialog();
    }
}

bool DEBlockGroup::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_Bar || watched == m_BarLabel || watched == m_BarIcon)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            m_StyleSheet = m_Bar->styleSheet();
            m_LabelStyleSheet = m_BarLabel->styleSheet();
            //整条标题栏一起变黄
            m_Bar->setStyleSheet("background-color:#C1D188");
            m_BarLabel->setStyleSheet("background-color:#C1D188;"
                                      "color: rgb(0, 103, 124);");
            m_BarIcon->setStyleSheet("background-color:#C1D188");
            return true;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            //还原
            m_Bar->setStyleSheet(m_StyleSheet);
            m_BarLabel->setStyleSheet(m_LabelStyleSheet);
            m_BarIcon->setStyleSheet(m_StyleSheet);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void DEBlockGroup::AdjustHeight()
{
    this->adjustSize();
}

void DEBlockGroup::SetExpanded(bool bExpand)
{
    DEBlockLayoutBase::SetExpanded(bExpand);

    SetIcon();

    m_pCtrlBox->setVisible(b_Expanded);
    adjustSize();

    DEBlockLayoutBase* layout = (DEBlockLayoutBase*)this->GetParentLayout();
    while(layout)
    {
        DEBlockLayoutBase* ParentLayout = (DEBlockLayoutBase*)layout->GetParentLayout();
        ParentLayout->GetBlockBox()->adjustSize();
        ParentLayout->adjustSize();
        layout = ParentLayout;
    }
}

DEBlockBox* DEBlockGroup::GetBlockBox()
{
    return m_pCtrlBox;
}

void DEBlockGroup::SetBackgroudColor(int type)
{
    DEBlockLayoutBase::SetBackgroudColor(type);
    setAttribute(Qt::WA_StyledBackground);//设置与父widget不同背景色

    QString BackGroundColor;
    switch (type)
    {
    case 0:
        BackGroundColor = ("background: rgb(255, 255, 255)");
        break;
    case 1:
        BackGroundColor = ("background: rgb(218, 222, 255)");
        break;
    }

    setStyleSheet(BackGroundColor);
    m_pCtrlBox->setStyleSheet(BackGroundColor);
    m_Bar->setStyleSheet(BackGroundColor);
}

void DEBlockGroup::SetEnable(bool bEnable)
{
    DEBlockLayoutBase::SetEnable(bEnable);

    m_BarLabel->setEnabled(bEnable);
    m_BarIcon->setEnabled(bEnable);
    m_Bar->setEnabled(bEnable);
    m_pCtrlBox->setEnabled(bEnable);
}

int DEBlockGroup::Column()
{
    return m_pCtrlBox->Column();
}

void DEBlockGroup::SetColumn(int num)
{
    m_pCtrlBox->SetColumnNum(num);
}
