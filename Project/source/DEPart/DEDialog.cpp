#include "DEDialog.h"
#include "ui_DEDialog.h"
#include "DEBlockContainer.h"
#include "DEBlock.h"
#include "UICommFun.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QMoveEvent>

DEDialog::DEDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DEDialog)
{
    ui->setupUi(this);
    m_parent = parent;
    m_PressPopPos.setX(0);
    m_PressPopPos.setY(0);
    m_pMode = DialogCreate;
    setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);

    m_pBlockContainer = new DEBlockContainer(this);
    InitButtonBox();

//    UIMainWindow *myWidget = (UIMainWindow*)parent;
//    connect(myWidget, &UIMainWindow::UIChanged, this, &DEDialog::changePos);
    int x = 0, y = 0;
    QStringList windowPos = settingReadPos("RecentPopWindowPos", x, y);
    DlgGetPos(x, y);
    move(x, y);
}

DEDialog::~DEDialog()
{
    QPoint point(this->frameGeometry().x(), this->frameGeometry().y());
    QPoint parentPoint = m_parent->mapToGlobal(QPoint(0, 0));
    settingWritePos("RecentPopWindowPos", point, parentPoint, false);
    delete ui;
}

void DEDialog::resizeEvent(QResizeEvent *event)
{
    QSize sSize = size();
    int iboxTop = sSize.height() - 30;
    int iBoxRight = sSize.width() - 10;
    sSize.setHeight(iboxTop);
    if(m_pBlockContainer)
        m_pBlockContainer->setFixedSize(sSize);

    QRect boxRect = m_pButtonBox->geometry();
    boxRect.moveTop(iboxTop);
    boxRect.moveRight(iBoxRight);
    m_pButtonBox->setGeometry(boxRect);

    return QWidget::resizeEvent(event);
}

void DEDialog::InitButtonBox()
{
    m_pButtonBox = new QWidget(this);
    m_pButtonBox->setFixedSize(175, 30);

    m_pOkButton = new QPushButton(m_pButtonBox);
    m_pOkButton->setFixedSize(55, 20);
    m_pOkButton->setText(QObject::tr("确定"));

    m_pApplyButton = new QPushButton(m_pButtonBox);
    m_pApplyButton->setFixedSize(55, 20);
    m_pApplyButton->setText(QObject::tr("应用"));

    m_pCancelButton = new QPushButton(m_pButtonBox);
    m_pCancelButton->setFixedSize(55, 20);
    m_pCancelButton->setText(QObject::tr("取消"));

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing(5);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_pOkButton);
    layout->addStretch();
    layout->addWidget(m_pApplyButton);
    layout->addStretch();
    layout->addWidget(m_pCancelButton);
    m_pButtonBox->setLayout(layout);

    connect(m_pOkButton, &QPushButton::clicked, this, &DEDialog::accept);
    connect(m_pApplyButton, &QPushButton::clicked, this, &DEDialog::apply);
    connect(m_pCancelButton, &QPushButton::clicked, this, &DEDialog::reject);
}

void DEDialog::accept()
{
    QDialog::accept();
    emit DialogClosed();
}

void DEDialog::reject()
{
    QDialog::reject();
    emit DialogClosed();
}

void DEDialog::apply()
{
    QDialog::accept();
    emit DialogClosed();
}

void DEDialog::AllBlockInit()
{
    QMap<QString, DEBlock*> map = m_pBlockContainer->GetBlockMap();
    for(auto it = map.begin(); it != map.end(); it++)
    {
        DEBlock* pBlock = it.value();
        pBlock->BlockInitialize();
        pBlock->setEnabled(pBlock->Enable());
    }

    for(auto it = map.begin(); it != map.end(); it++)
    {
        DEBlock* pBlock = it.value();
        pBlock->SetVisible(pBlock->Show());
    }

    m_pBlockContainer->Invalidate();
}

void DEDialog::SetDialogMode(DialogMode mode)
{
    m_pMode = mode;
    if(m_pMode == DialogCreate)
    {
        m_pApplyButton->setVisible(true);
        m_pButtonBox->setFixedSize(175, 30);
    }
    else
    {
        m_pApplyButton->setVisible(false);
        m_pButtonBox->setFixedSize(115, 30);
    }
}

void DEDialog::SetOkAndApplyButtonEnable(bool bEnable)
{
    m_pOkButton->setEnabled(bEnable);
    m_pApplyButton->setEnabled(bEnable);
}

void DEDialog::changePos(QPoint pMove)
{
    int x = 0, y = 0;
    if(m_parent)
    {
        if(m_PressPopPos.isNull())//子窗口关闭,未移动
        {
            QStringList windowPos = settingReadPos("RecentPopWindowPos", x, y);
            if(!windowPos.isEmpty())
            {
                x += pMove.x();
                y += pMove.y();
            }
            else//默认值
            {
                x = pMove.x() + (m_parent->width() - this->frameSize().width());
                y = pMove.y() + (m_parent->height() - this->frameSize().height());
            }
        }
        else//子窗口移动
        {
            x = pMove.x() + m_PressPopPos.x();
            y = pMove.y() + m_PressPopPos.y();
        }
    }

    //随着主窗口移动,对话框四个角不能超出屏幕
    QSize popSize = this->frameSize();
    CalPopWindowAccordBoder(x, y, popSize);
    move(x, y);
}

void DEDialog::moveEvent(QMoveEvent *event)
{
    if(isVisible())
    {
        settingWritePos("RecentPopWindowPos", event->pos(), m_parent->pos(), false);
        event->accept();
    }
}

void DEDialog::CurrentPopPos(QPoint pMove)
{
    m_PressPopPos.setX(this->frameGeometry().x() - pMove.x());
    m_PressPopPos.setY(this->frameGeometry().y() - pMove.y());
}
