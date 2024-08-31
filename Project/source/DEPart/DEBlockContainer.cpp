#include "DEBlockContainer.h"
#include "DEBlockBox.h"
#include "DEBlock.h"
#include <QScrollBar>
#include <QEvent>
#include <QDebug>

DEBlockContainer::DEBlockContainer(QWidget* parent) : QWidget(parent)
{
    m_pDialog = parent;
    setStyleSheet("background: rgb(218, 222, 225)");

    m_pScrollArea = new QScrollArea(this);
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pScrollArea->verticalScrollBar()->installEventFilter(this);

    m_pBlockBox = new DEBlockBox(m_pScrollArea);
    m_pBlockBox->SetBlockBoxMargin(0);
    m_pScrollArea->setWidget(m_pBlockBox);

    this->installEventFilter(this);
}

DEBlockContainer::~DEBlockContainer()
{

}

void DEBlockContainer::resizeEvent(QResizeEvent *event)
{
    QSize sSize = size();
    m_pScrollArea->setFixedSize(sSize);
    int width = sSize.width();
    m_pBlockBox->setFixedWidth(width);
    return QWidget::resizeEvent(event);
}

QString DEBlockContainer::GetClassName()
{
    return "DEBlockContainer";
}

bool DEBlockContainer::eventFilter(QObject *watched, QEvent *event)
{
    if(!m_pScrollArea || !m_pBlockBox)
        return QWidget::eventFilter(watched, event);

    switch(event->type())
    {
    case QEvent::Resize:
    {
        if(watched->inherits("DEBlockContainer"))
        {
            //检查当前是否有滚动条, 如果有则减去滚动条的宽度
            bool bShow = m_pScrollArea->verticalScrollBar()->isVisible();
            int iScrollBarWidth = m_pScrollArea->verticalScrollBar()->width();
            if(m_pScrollArea)
                m_pScrollArea->setFixedSize(size());
            if(m_pBlockBox)
                m_pBlockBox->setFixedWidth(width() - (bShow ? iScrollBarWidth : 0));
        }
        break;
    }
    case QEvent::Show:
    case QEvent::Hide:
    {
        if(watched->inherits("QScrollBar"))
        {
            int iScrollBarWidth = m_pScrollArea->verticalScrollBar()->width();
            int w = width() - ((event->type() == QEvent::Show) ? iScrollBarWidth : 0);
            if(m_pBlockBox)
                m_pBlockBox->setFixedWidth(w);
        }
        break;
    }
    default:
        break;
    }

    return QWidget::eventFilter(watched, event);
}

void DEBlockContainer::ResizeContainerAndDialog()
{
    QSize size = m_pBlockBox->size();
    int h = size.height() + 32;
    size.setHeight(h);
    m_pDialog->resize(size);
}

void DEBlockContainer::AdjustCtrlBoxSize()
{
    m_pBlockBox->adjustSize();
}

//这些调整对话框效果等我再调调
void DEBlockContainer::Invalidate()
{
    AdjustCtrlBoxSize();
    QSize CtrlBoxSize = m_pBlockBox->size();
    int BoxH = CtrlBoxSize.height();

    QSize DlgSize = m_pDialog->size();
    DlgSize.setHeight(BoxH + 32);
    m_pDialog->resize(DlgSize);

    QSize ContainerSize = DlgSize;
    ContainerSize.setHeight(ContainerSize.height() - 30);
    setFixedSize(ContainerSize);
}

void DEBlockContainer::InvalidateAll()
{
    AdjustCtrlBoxSize();
    ResizeContainerAndDialog();
}

void DEBlockContainer::AddBlock(DEBlock* pBlock)
{
    m_BlockIDMap.insert(pBlock->Name(), pBlock);
}

DEBlock* DEBlockContainer::FindBlock(QString BlockID)
{
    auto it = m_BlockIDMap.find(BlockID);
    if(it != m_BlockIDMap.end())
        return it.value();
    return nullptr;
}


