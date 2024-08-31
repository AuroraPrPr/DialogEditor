#ifndef DEBLOCKCONTAINER_H
#define DEBLOCKCONTAINER_H

#include "DEPart_global.h"
#include "DECommon.h"
#include <QWidget>
#include <QScrollArea>
#include <QMap>

class DEBlockBox;
class DEBlock;
class DEPART_EXPORT DEBlockContainer : public QWidget
{
public:
    explicit DEBlockContainer(QWidget* parent = nullptr);
    ~DEBlockContainer();

    QString GetClassName();
    bool eventFilter(QObject *watched, QEvent *event);

    void AdjustCtrlBoxSize();
    void ResizeContainerAndDialog();
    inline DEBlockBox* GetBlockBox()
    {
        return m_pBlockBox;
    }
    inline QMap<QString, DEBlock*> GetBlockMap()
    {
        return m_BlockIDMap;
    }

    void Invalidate();
    void InvalidateAll();

    void AddBlock(DEBlock* pBlock);
    DEBlock* FindBlock(QString BlockID);
protected:
    void resizeEvent(QResizeEvent *) override;
private:
    QWidget* m_pDialog;
    QScrollArea* m_pScrollArea;
    DEBlockBox* m_pBlockBox;

    QMap<QString, DEBlock*> m_BlockIDMap;
};

#endif // DEBLOCKCONTAINER_H
