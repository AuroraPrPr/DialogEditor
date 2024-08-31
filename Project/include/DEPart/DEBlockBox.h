#ifndef DEBLOCKBOX_H
#define DEBLOCKBOX_H

#include "DEPart_global.h"
#include "DECommon.h"
#include <QWidget>
#include <QGridLayout>

class DEBlock;
class DEPART_EXPORT DEBlockBox : public QWidget
{
public:
    explicit DEBlockBox(QWidget* parent = nullptr);
    ~DEBlockBox();

    void AddBlockToBox(DEBlock* Ctrl);
    void AddBlockToBox(DEBlock* Ctrl, int row, int column);
    inline int Column(){return i_Column;};
    void SetColumnNum(int Column);
    void SetBlockBoxMargin(int type);

    //读取xml制成对话框
    //void AddAllWidgetsToBox(std::vector<QWidget*> pCtrls, std::vector<CtrlInfo> infos);

private:
    QGridLayout* m_pLayout;
    int i_Column;

    std::vector<DEBlock*> m_pBlocks;
};

#endif // DEBLOCKBOX_H
