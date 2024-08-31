#ifndef DEMAINWIDGET_H
#define DEMAINWIDGET_H

#include "DEBlockTree.h"
#include "DEDialogTree.h"
#include "DEPropTree.h"

class DEBlock;
class DEDialog;

class DEMainWidget : public QWidget
{
    Q_OBJECT
public:
    DEMainWidget(QWidget* parent = nullptr);

public:
    QDomElement CreateBlockElement(QString type);
    DEBlock* CreateBlockFromElement(DEDialog* pDlg, QDomElement e);

    void DialogRefresh();
    void DialogClose();
    void AddChildBlockToBlock(DEDialog* pDlg, QDomElement parent, DEBlock* parentBlock);

    void Refresh(QString BlockID = "DEDialog");
    void Close();
    void BlockDelete();
    void BlockMoveUp();
    void BlockMoveDown();

    void RemoveChild(QDomElement e);
private:
    QString GetTypeFromBlockTree(QString LabelType);

public slots:
    void AddBlock(QString type);
    void DialogClosed();
    void RefreshPropTree(QString BlockID);
    void BlockPropChanged(bool bDialogTreeRefresh);

private:
    DEBlockTree* m_BlockTree;
    DEDialogTree* m_DialogTree;
    DEPropTree* m_PropTree;
    DEDialog* m_pDlg;
};

#endif // DEMAINWIDGET_H
