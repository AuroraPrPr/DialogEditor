#include "DECtrlLineEdit.h"

DECtrlLineEdit::DECtrlLineEdit(QWidget* parent)
    : QLineEdit(parent)
{
    setCursor(Qt::IBeamCursor);
    setStyleSheet("border: 1px solid gray");
}

void DECtrlLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit focusIn();
}
void DECtrlLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit focusOut();
}
void DECtrlLineEdit::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QLineEdit::mousePressEvent(e);
}
//老版本Qt的问题,小键盘的回车不是确认
//void DECtrlLineEdit::keyPressEvent(QKeyEvent *e)
//{
//    if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
//    {

//    }
//    QLineEdit::keyPressEvent(e);
//}
