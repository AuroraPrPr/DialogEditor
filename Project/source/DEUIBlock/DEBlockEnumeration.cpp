#include "DEBlockEnumeration.h"

DEBlockEnumeration::DEBlockEnumeration(QWidget* parent, QString BlockID, QString Label)
    : DEBlockBasicBase(parent, BlockID, Label)
{
    m_Style = OptionMenu;
    b_LabelVisible = true;
    m_RadioStyle = vertical;
    i_CurIndex = 0;
    i_Columns = 0;

    //OptionMenu
    m_pCombox = new QComboBox();
    m_pCombox->setFixedHeight(27);
    m_pCombox->setStyleSheet(QString(R"(
                                     QComboBox{
                                     border: 1px solid gray;
                                     padding: 0px, 0px, 0px, 0px;
                                     }
                                     QComboBox::item{
                                     height: 25px;
                                     }
                                     QComboBox::down-arrow{
                                     width: 8px;
                                     left: 2px;
                                     }
                                     QComboBox::drop-down{
                                     border: 1px
                                     padding: 10px, 10px, 10px, 10px;
                                     }
                                     )"));
    QListView *list = new QListView(this);
    m_pCombox->setView(list);
    m_pCombox->setIconSize(QSize(SIconSize, SIconSize));
    m_pCombox->installEventFilter(this);
    connect(m_pCombox, &QComboBox::currentTextChanged,
            this, &DEBlockEnumeration::ComboxTextChanged);

    m_pHLayout = new QHBoxLayout();
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(6, 0, 4, 0);

    //RadioBox
    m_pButtonGroup = new QButtonGroup;
    connect(m_pButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &DEBlockEnumeration::RadioBoxButtonChecked);

    m_pTopWidget = new QWidget();
    m_pButtomWidget = new QWidget();

    m_pVLayout = new QVBoxLayout();
    m_pVLayout->setSpacing(0);
    m_pVLayout->setContentsMargins(6, 0, 4, 0);

    m_pGridLayout = new QGridLayout(m_pButtomWidget);
    m_pGridLayout->setSpacing(0);
    m_pGridLayout->setContentsMargins(0, 0, 0, 0);

    //PullDown
    m_pPullButton = new QPushButton();
    m_pPullButton->setFixedWidth(20);
    m_pPullButton->setStyleSheet(QString(R"(
                                         QPushButton{
                                         border: none;
                                         }
                                         QPushButton::menu-indicator{
                                         subcontrol-position: center center;
                                         }
                                         )"));
    m_pActionGroup = new QActionGroup(m_pPullButton);
    connect(m_pActionGroup, &QActionGroup::triggered,
            this, &DEBlockEnumeration::PullDownItemChecked);
}

DEBlockEnumeration::~DEBlockEnumeration()
{
    if(m_pCombox) {delete m_pCombox; m_pCombox = nullptr;}
    if(m_pHLayout) {delete m_pHLayout; m_pHLayout = nullptr;}
    if(m_pTopWidget) {delete m_pTopWidget; m_pTopWidget = nullptr;}
    if(m_pButtomWidget) {delete m_pButtomWidget; m_pButtomWidget = nullptr;}
    if(m_pVLayout) {delete m_pVLayout; m_pVLayout = nullptr;}
    if(m_pPullButton) {delete m_pPullButton; m_pPullButton = nullptr;}
}

void DEBlockEnumeration::BlockInitialize()
{
    DEBlock::BlockInitialize();
    switch (m_Style)
    {
    case OptionMenu:
    {
        if(b_LabelVisible)
        {
            m_pHLayout->addWidget(m_pLabel);
            m_pCombox->setFixedWidth(145);
        }
        m_pHLayout->addWidget(m_pCombox);
        m_pWidget->setLayout(m_pHLayout);
        m_pWidget->setFixedHeight(BlockHeight);

        AddOptionMenuEnum();
        break;
    }
    case RadioBox:
    {
        if(b_LabelVisible)
        {
            m_pHLayout->addWidget(m_pLabel);
            m_pTopWidget->setLayout(m_pHLayout);
            m_pTopWidget->setFixedHeight(24);
            m_pVLayout->addWidget(m_pTopWidget);
        }
        m_pVLayout->addWidget(m_pButtomWidget);
        m_pButtomWidget->setLayout(m_pGridLayout);
        m_pWidget->setLayout(m_pVLayout);

        AddRadioBoxEnum();
        break;
    }
    case PullDown:
    {
        m_pHLayout->addWidget(m_pPullButton, Qt::AlignLeft);
        m_pHLayout->addStretch();
        m_pWidget->setLayout(m_pHLayout);
        m_pWidget->setFixedHeight(BlockHeight);

        AddPullDownEnum();
        break;
    }
    default:
        break;
    }
}

void DEBlockEnumeration::AddOptionMenuEnum()
{
    if(m_EnumMembers.empty())
        return;

    m_pCombox->blockSignals(true);
    m_pCombox->addItems(m_EnumMembers);
    if(!m_Icons.empty() && m_Icons.size() <= m_EnumMembers.size())
    {
        for(int index = 0; index < m_Icons.size(); index++)
        {
            m_pCombox->setItemIcon(index, QPixmap(m_Icons[index]));
        }
    }
    m_pCombox->setCurrentIndex(i_CurIndex);

    if(m_EnumSensitivity.size() == m_EnumMembers.size())
    {
        for(int i=0; i<m_EnumMembers.size(); i++)
        {
            if(m_EnumSensitivity[i] == 1)
                continue;

            QVariant v0(0);//不可选
            QModelIndex index = m_pCombox->model()->index(i, 0);
            m_pCombox->model()->setData(index, v0, Qt::UserRole - 1);
        }
    }
    m_pCombox->blockSignals(false);
}

void DEBlockEnumeration::AddRadioBoxEnum()
{
    if(m_EnumMembers.empty())
        return;

    if(m_RadioStyle == vertical)
    {
        if(i_Columns <= 1)//默认 1列
        {
            for (int i=0; i < m_EnumMembers.size(); i++)
            {
                QString sText = m_EnumMembers.at(i);
                QRadioButton* button = new QRadioButton(sText);
                m_pGridLayout->addWidget(button);
                m_pButtonGroup->addButton(button, i);
                if(i == i_CurIndex)
                    button->setChecked(true);
            }
        }
        else
        {
            int size = m_EnumMembers.size();
            std::vector<int> Row(size), Column(size);
            //顺序为从左至右，从上至下
            for(int i=0; i<size; i++)
            {
                Row[i] = i/i_Columns;
                Column[i] = i - Row[i]*i_Columns;
            }

            for(int i=0; i<size; i++)
            {
                QString sText = m_EnumMembers.at(i);
                QRadioButton* button = new QRadioButton(sText);
                m_pGridLayout->addWidget(button, Row[i], Column[i]);
                m_pButtonGroup->addButton(button, i);
                if(i == i_CurIndex)
                    button->setChecked(true);
            }
        }
    }
    else  //m_RadioStyle == horizontal
    {
        int size = m_EnumMembers.size();
        for(int i=0; i<size; i++)
        {
            QString sText = m_EnumMembers.at(i);
            QRadioButton* button = new QRadioButton(sText);
            m_pGridLayout->addWidget(button, 0, i);
            m_pButtonGroup->addButton(button, i);
            if(i == i_CurIndex)
                button->setChecked(true);
        }
    }

    if(m_EnumSensitivity.size() == m_EnumMembers.size())
    {
        for(int i=0; i<m_EnumMembers.size(); i++)
        {
            if(m_EnumSensitivity[i] == 1)
                continue;

            m_pButtonGroup->button(i)->setEnabled(false);
        }
    }
}

void DEBlockEnumeration::AddPullDownEnum()
{
    if(m_EnumMembers.empty())
        return;

    QMenu* menu = new QMenu(m_pPullButton);
    menu->setStyleSheet(QString(R"(
                                QMenu::item::selected{
                                background-color: #C1D1B8;
                                }
                                )"));

    for (int i=0; i < m_EnumMembers.size(); i++)
    {
        QAction* action = new QAction(menu);
        action->setText(m_EnumMembers.at(i));
        action->setCheckable(true);
        m_pActionGroup->addAction(action);
        if(i == i_CurIndex)
            action->setChecked(true);
    }
    menu->addActions(m_pActionGroup->actions());
    m_pPullButton->setMenu(menu);

    if(m_EnumSensitivity.size() == m_EnumMembers.size())
    {
        for(int i=0; i<m_EnumMembers.size(); i++)
        {
            if(m_EnumSensitivity[i] == 1)
                continue;

            m_pActionGroup->actions()[i]->setEnabled(false);
        }
    }
}

QString DEBlockEnumeration::Type()
{
    return "Enumeration";
}

void DEBlockEnumeration::SetBackgroudColor(int type)
{
    DEBlockBasicBase::SetBackgroudColor(type);
    setAttribute(Qt::WA_StyledBackground);
    switch(type)
    {
    case 0:
        setStyleSheet("background: rgb(255, 255, 255)");
        m_pTopWidget->setStyleSheet("background: rgb(255, 255, 255)");
        m_pButtomWidget->setStyleSheet("background: rgb(255, 255, 255)");
        break;
    case 1:
        setStyleSheet("background: rgb(218, 222, 255)");
        m_pTopWidget->setStyleSheet("background: rgb(218, 222, 255)");
        m_pButtomWidget->setStyleSheet("background: rgb(218, 222, 255)");
        break;
    }
}

void DEBlockEnumeration::SetEnable(bool bEnable)
{
    DEBlockBasicBase::SetEnable(bEnable);
    m_pLabel->setEnabled(bEnable);
    m_pCombox->setEnabled(bEnable);
    m_pButtomWidget->setEnabled(bEnable);
}

bool DEBlockEnumeration::eventFilter(QObject* watched, QEvent* event)
{
    if(watched == m_pCombox)
    {
        if(event->type() == QEvent::Wheel)
        {
            return true;//屏蔽鼠标滚轮事件
        }
    }
    return QWidget::eventFilter(watched, event);
}


void DEBlockEnumeration::SetCallBackFun_ComboxTextChanged(CallBack1 pFun)
{
    m_pEnumerationIndexChanged = pFun;
}
void DEBlockEnumeration::SetCallBackFun_RadioBoxButtonChecked(CallBack1 pFun)
{
    m_pEnumerationIndexChanged = pFun;
}
void DEBlockEnumeration::SetCallBackFun_PullDownItemChecked(CallBack1 pFun)
{
    m_pEnumerationIndexChanged = pFun;
}

void DEBlockEnumeration::ComboxTextChanged(const QString text)
{
    i_CurIndex = m_pCombox->currentIndex();
    if(m_pEnumerationIndexChanged)
        m_pEnumerationIndexChanged(m_pDialog);

    emit EnumerationIndexChanged();
}
void DEBlockEnumeration::RadioBoxButtonChecked(int ID)
{
    i_CurIndex = ID;
    if(m_pEnumerationIndexChanged)
        m_pEnumerationIndexChanged(m_pDialog);

    emit EnumerationIndexChanged();
}
void DEBlockEnumeration::PullDownItemChecked(QAction* action)
{
    i_CurIndex = m_pActionGroup->actions().indexOf(action);
    if(m_pEnumerationIndexChanged)
        m_pEnumerationIndexChanged(m_pDialog);

    emit EnumerationIndexChanged();
}

void DEBlockEnumeration::SetEnumerationStyle(EnumerationStyle style)
{
    m_Style = style;
    //已经初始化后再设置样式不改变效果
}
EnumerationStyle DEBlockEnumeration::GetnumerationStyle()
{
    return m_Style;
}

void DEBlockEnumeration::SetCurIndex(int index)
{
    i_CurIndex = index;
    if(b_Init)
    {
        switch(m_Style)
        {
        case OptionMenu:
            m_pCombox->setCurrentIndex(index);
            break;
        case RadioBox:
            m_pButtonGroup->button(index)->setChecked(true);
            break;
        case PullDown:
            m_pActionGroup->actions()[index]->setChecked(true);
            break;
        default:
            break;
        }
    }
}
int DEBlockEnumeration::GetCurIndex()
{
   return i_CurIndex;
}

void DEBlockEnumeration::SetLabelVisibility(bool bVisible)
{
    b_LabelVisible = bVisible;
}
bool DEBlockEnumeration::GetLabelVisibility()
{
    return b_LabelVisible;
}

void DEBlockEnumeration::SetBitmaps(QStringList Icons)
{
    m_Icons = Icons;
}
QStringList DEBlockEnumeration::GetBitmaps()
{
    return m_Icons;
}

void DEBlockEnumeration::SetEnumMembers(QStringList members)
{
    m_EnumMembers = members;
    if(m_EnumSensitivity.empty())
    {
        m_EnumSensitivity.resize(m_EnumMembers.size(), 1);
    }
}
QStringList DEBlockEnumeration::GetEnumMembers()
{
    return m_EnumMembers;
}

void DEBlockEnumeration::SetIndexEnable(int index, bool bEnable)
{
    if(index > -1 && index < m_EnumSensitivity.size())
    {
        m_EnumSensitivity[index] = bEnable;
    }
    if(b_Init)
    {
        switch(m_Style)
        {
        case OptionMenu:
        {
            QModelIndex Index = m_pCombox->model()->index(index, 0);
            if(bEnable)
            {
                QVariant v1(1|32);
                m_pCombox->model()->setData(Index, v1, Qt::UserRole - 1);
            }
            else
            {
                QVariant v0(0);
                m_pCombox->model()->setData(Index, v0, Qt::UserRole - 1);
            }
            break;
        }
        case RadioBox:
            m_pButtonGroup->button(index)->setChecked(bEnable);
            break;
        case PullDown:
            m_pActionGroup->actions()[index]->setChecked(bEnable);
            break;
        default:
            break;
        }
    }
}
bool DEBlockEnumeration::GetIndexEnable(int index)
{
    if(index > -1 && index < m_EnumSensitivity.size())
    {
        return m_EnumSensitivity[index];
    }
    return true;
}

void DEBlockEnumeration::SetEnumSensitivity(std::vector<int> value)
{
    m_EnumSensitivity = value;
}
std::vector<int> DEBlockEnumeration::GetEnumSensitivity()
{
    return m_EnumSensitivity;
}

void DEBlockEnumeration::SetRadioBoxStyle(RadioBoxLayoutStyle style)
{
    m_RadioStyle = style;
}
RadioBoxLayoutStyle DEBlockEnumeration::radioBoxStyle()
{
    return m_RadioStyle;
}

void DEBlockEnumeration::SetRadioBoxColumn(int num)
{
    i_Columns = num;
}
int DEBlockEnumeration::RadioBoxColumn()
{
    return i_Columns;
}
