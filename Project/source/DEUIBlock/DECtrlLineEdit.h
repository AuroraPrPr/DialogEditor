#ifndef DECTRLLINEEDIT_H
#define DECTRLLINEEDIT_H

#include "DEUIBlock_global.h"

class DECtrlLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit DECtrlLineEdit(QWidget* parent = nullptr);

protected:
    virtual void focusInEvent(QFocusEvent *) override;
    virtual void focusOutEvent(QFocusEvent *) override;
    virtual void mousePressEvent(QMouseEvent *) override;

signals:
    void focusIn();
    void focusOut();
    void clicked();
};

#endif // DECTRLLINEEDIT_H
