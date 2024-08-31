#include "DEBlockSelectBase.h"
#include "DEBlockLayoutBase.h"

DEBlockSelectBase::DEBlockSelectBase(QWidget* parent, QString BlockID, QString Label)
    : DEBlock(parent, BlockID, Label)
{
    m_pLabelWrap = new QWidget(parent);
    m_pLabelWrap->installEventFilter(this);

    m_pResultIcon = new QLabel(m_pLabelWrap);
    m_pResultIcon->setFixedSize(16, 16);
    m_pResultIcon->setPixmap(QPixmap(":/Icon/Icon/Required.png"));
    m_pResultIcon->setAttribute(Qt::WA_TranslucentBackground);

    m_StepStatus = Required;
    m_SelectMode = Single;
    s_ActiveStyleSheet = QString(R"(
                                 QWidget{
                                 background: rgb(255, 215, 0);
                                 border: none;
                                 }
                                 )");
}

void DEBlockSelectBase::BlockInitialize()
{
    DEBlock::BlockInitialize();

    QHBoxLayout* WarpLayout = new QHBoxLayout();
    WarpLayout->setSpacing(2);
    WarpLayout->setContentsMargins(0, 0, 0, 0);

    WarpLayout->addWidget(m_pResultIcon);
    WarpLayout->addWidget(m_pLabel);

    if(m_StepStatus == Required)
    {
        m_pResultIcon->setPixmap(QPixmap(":/Icon/Icon/Required.png"));
    }
    else if(m_StepStatus == Optional)
    {
        m_pResultIcon->setVisible(false);
    }
    else if(m_StepStatus == SatisFied)
    {
        m_pResultIcon->setPixmap(QPixmap(":/Icon/Icon/SatisFied.png"));
    }

    m_pLabelWrap->setLayout(WarpLayout);

    SetResultNum(0);
}

void DEBlockSelectBase::SetCtrlActive()
{
    m_pLabelWrap->setStyleSheet(s_ActiveStyleSheet);
    s_StyleSheet = s_ActiveStyleSheet;
    emit SelectBlockActive();
}

void DEBlockSelectBase::SetCtrlEnd()
{
    m_pLabelWrap->setStyleSheet(s_UnActiveStyleSheet);
    s_StyleSheet = s_UnActiveStyleSheet;
}

void DEBlockSelectBase::SetBackgroudColor(int type)
{
    DEBlock::SetBackgroudColor(type);
    setAttribute(Qt::WA_StyledBackground);
    switch(type)
    {
    case 0:
        s_UnActiveStyleSheet = "background: rgb(255, 255, 255)";
        break;
    case 1:
        s_UnActiveStyleSheet = "background: rgb(218, 222, 255)";
        break;
    }
    m_pLabelWrap->setStyleSheet(s_UnActiveStyleSheet);
}

void DEBlockSelectBase::SetEnable(bool bEnable)
{
    DEBlock::SetEnable(bEnable);
    m_pLabelWrap->setEnabled(bEnable);
}

void DEBlockSelectBase::SetShow(bool bShow)
{
    DEBlock::SetShow(bShow);

    if(b_Init)
    {
        DEBlock* Block = this;
        while(Block->GetParentLayout())
        {
            DEBlockLayoutBase* ParentLayout = (DEBlockLayoutBase*)Block->GetParentLayout();
            int width = ParentLayout->size().width();
            int Hbefore = ParentLayout->GetBlockBox()->size().height();
            ParentLayout->GetBlockBox()->adjustSize();
            int Hafter = ParentLayout->GetBlockBox()->size().height();
            ParentLayout->GetBlockBox()->resize(width, Hafter);

            QSize size = ParentLayout->size();
            int h = size.height() + Hafter - Hbefore;
            size.setHeight(h);
            ParentLayout->resize(size);
            Block = ParentLayout;
        }
    }
}

void DEBlockSelectBase::StepStatusChanged(StepStatus step)
{
    m_StepStatus = step;

    if(b_Init)
    {
        if(m_StepStatus == Required)
        {
            m_pResultIcon->setPixmap(QPixmap(":/Icon/Icon/Required.png"));
        }
        else if(m_StepStatus == Optional)
        {
            m_pResultIcon->setVisible(false);
        }
        else if(m_StepStatus == SatisFied)
        {
            m_pResultIcon->setPixmap(QPixmap(":/Icon/Icon/SatisFied.png"));
        }
    }
}
StepStatus DEBlockSelectBase::GetStatusChanged()
{
    return m_StepStatus;
}

void DEBlockSelectBase::SetSelectMode(SelectMode mode)
{
    m_SelectMode = mode;
}
SelectMode DEBlockSelectBase::GetSelectMode()
{
    return m_SelectMode;
}

void DEBlockSelectBase::SetResultNum(int num)
{
    QString numstr = QString::number(num);
    QString Label = s_Label + "(" + numstr + ")";
    m_pLabel->setText(Label);
}

bool DEBlockSelectBase::eventFilter(QObject* watched, QEvent* event)
{
    if(watched == m_pLabelWrap)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* MouseEvent = static_cast<QMouseEvent*>(event);
            if(MouseEvent->button() == Qt::LeftButton)
            {
                SetCtrlActive();
            }
        }
        if(event->type() == QEvent::Enter)
        {
            s_StyleSheet = m_pLabelWrap->styleSheet();
            m_pLabelWrap->setStyleSheet("background-color: rgb(175, 215, 225)");
        }
        if(event->type() == QEvent::Leave)
        {
            m_pLabelWrap->setStyleSheet(s_StyleSheet);
        }
        return true;
    }
    return QWidget::eventFilter(watched, event);
}
