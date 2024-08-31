#include <QDesktopWidget>
#include <QApplication>
#include <QSettings>

/**
 * @brief 计算子窗口需要移动到的位置点(x, y),且随着主窗口的移动不能超出边界
 * @param x
 * @param y
 * @param popWinSize
 */
extern void CalPopWindowAccordBoder(int &x, int &y, QSize popWinSize)
{
    QDesktopWidget *desk = QApplication::desktop();
    //不包含任务栏,包含的是screenGeometry
    //desk的width和height是所以屏幕的宽与高,默认多屏时左下为主屏幕
    QRect sizeRect = desk->availableGeometry();
    int left = sizeRect.left();
    int bottom = sizeRect.bottom();
    int right = desk->width() - left;
    int top = desk->height() - bottom;


    if(x < left){
        x = left;
    }

    if(y < top){
        y = top;
    }

    if(x + popWinSize.width() > right){
        x = right - popWinSize.width();
    }

    if(y + popWinSize.height() > bottom){
        y = bottom - popWinSize.height();
    }
}

/**
 * @brief 将窗口位置写入注册表
 * @param valueName
 * @param point
 * @param parentPoint
 * @param isWrite
 */
extern void settingWritePos(QString valueName, QPoint point,
                            QPoint parentPoint, bool isWriteRelaValue)
{
    QSettings settings;
    QStringList windowPos = settings.value(valueName).toStringList();
    for(int i=windowPos.size()-1; i>0; i--)
    {
        windowPos.removeLast();
    }

    QString posString;
    if(isWriteRelaValue)//true记录相对位置, false记录绝对位置
    {
        posString = QObject::tr("%1,%2")
                .arg(point.x() - parentPoint.x())
                .arg(point.y() - parentPoint.y());
    }
    else
    {
        posString = QObject::tr("%1,%2").arg(point.x()).arg(point.y());
    }
    windowPos.prepend(posString);
    settings.setValue(valueName, windowPos);
}

/**
 * @brief 通过valueName从注册表中获取相应位置(x, y)
 * @param valueName
 * @param x
 * @param y
 * @return
 */
extern QStringList settingReadPos(QString valueName, int &x, int &y)
{
    QSettings settings;
    QStringList windowPos = settings.value(valueName).toStringList();
    if(!windowPos.isEmpty())
    {
        QString globalString = windowPos[0];
        QStringList pString = globalString.split(",");
        if(pString.size() == 2)
        {
            x = pString[0].toInt();
            y = pString[1].toInt();
        }
    }
    return windowPos;
}

/**
 * @brief DlgGetpos
 * @param x
 * @param y
 * @return
 */
extern bool DlgGetPos(int &x, int &y)
{
    QStringList windowPos = settingReadPos("RecentPopWindosPos", x, y);
    if(windowPos.isEmpty())
    {
        QDesktopWidget *desk = QApplication::desktop();
        x += desk->width()/2;
        y += desk->height()/2;
    }
    return true;
}
