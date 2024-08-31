#ifndef DEPARTCOLLECTION_H
#define DEPARTCOLLECTION_H

#include "DERoot.h"
#include <vector>
#include <QDomDocument>
class DEPart;

/**
 * @brief 文件管理类
 */
class DEROOT_EXPORT DEPartCollection
{
public:
    DEPartCollection(DERoot* root);
    DEPart* GetCurPart();

public:
    void FileNew();
    void FileOpen(QDomDocument* doc);
    void FileSave(QString FileName);
    void FileDelete();

private:
    DERoot* m_root;
    DEPart* m_CurPart;
};

#endif // PARTCOLLECTION_H
