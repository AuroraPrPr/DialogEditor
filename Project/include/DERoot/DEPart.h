#ifndef DEPART_H
#define DEPART_H

#include "DERoot.h"
#include <QDomDocument>
#include <QSet>

/**
 * @brief 文件类
 */
class DEROOT_EXPORT DEPart
{
public:
    DEPart();
    DEPart(QDomDocument* doc);
    ~DEPart();

    inline QDomDocument* GetXml() {return m_Xml;};
    QString GetAutoBlockID(QString type);

    void SetSaved(bool bSave = false);
    inline bool Saved() {return b_Saved;};
private:
    void ReadNodeChildrenID(QDomElement e);
private:
    bool b_Saved;
    QString s_Filename;
    QDomDocument* m_Xml;
    QSet<QString> m_BlockIDs;
};

#endif // DEPART_H
