#include "DEBlockObject.h"

DEBlockObject::DEBlockObject(QWidget* parent, QString BlockID, QString Label)
    : DEBlockSelectBase(parent, BlockID, Label)
{
    m_pIcon = new QLabel(this);
    m_pIcon->setPixmap(QPixmap(":/Icon/Icon/SelectObject.png"));
    m_pIcon->setStyleSheet(QString(R"(
                                   QLabel{
                                   border: 1px solid gray;
                                   }
                                   QLabel: hover{
                                   background-color: #C1D1B8;
                                   }
                                   QLabel: pressed{
                                   background-color: #A5AF9B;
                                   }
                                   QLabel: focus{
                                   outline: none;
                                   }
                                   )"));
    m_pIcon->setFixedSize(IconSize, IconSize);
}

void DEBlockObject::BlockInitialize()
{
    DEBlockSelectBase::BlockInitialize();

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(6, 0, 4, 0);

    layout->addWidget(m_pLabelWrap);
    layout->addWidget(m_pIcon, Qt::AlignRight);

    m_pWidget->setLayout(layout);
}

QString DEBlockObject::Type()
{
    return "SelectObject";
}

void DEBlockObject::SetEnable(bool bEnable)
{
    DEBlockSelectBase::SetEnable(bEnable);
    m_pIcon->setEnabled(bEnable);
}
