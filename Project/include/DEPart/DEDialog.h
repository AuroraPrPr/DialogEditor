#ifndef DEDIALOG_H
#define DEDIALOG_H

#include <QDialog>
#include "DEPart_global.h"

enum DialogMode
{
    DialogCreate,
    DialogEdit
};

namespace Ui {
class DEDialog;
}

class DEBlockContainer;
class DEPART_EXPORT DEDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DEDialog(QWidget *parent = nullptr);
    ~DEDialog();

    void AllBlockInit();

private:
    Ui::DEDialog *ui;
protected:
    void resizeEvent(QResizeEvent *) override;
protected:
    virtual void accept();
    virtual void reject();
    virtual void apply();
public:
    void moveEvent(QMoveEvent *event) override;
    void SetDialogMode(DialogMode mode);
    void SetOkAndApplyButtonEnable(bool bEnable);
public slots:
    void changePos(QPoint pMove);
    void CurrentPopPos(QPoint pMove);
private:
    void InitButtonBox();
signals:
    void DialogClosed();
protected:
    QWidget *m_parent;
    QPoint m_PressPopPos;
    DialogMode m_pMode;
public:
    DEBlockContainer *m_pBlockContainer;
    QWidget *m_pButtonBox;
    QPushButton *m_pOkButton;
    QPushButton *m_pApplyButton;
    QPushButton *m_pCancelButton;
};

#endif // DEDIALOG_H
