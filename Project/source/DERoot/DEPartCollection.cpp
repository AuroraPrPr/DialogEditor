#include "DEPartCollection.h"
#include "DEPart.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

DEPartCollection::DEPartCollection(DERoot* root)
{
    m_root = root;
    m_CurPart = nullptr;
}

DEPart* DEPartCollection::GetCurPart()
{
    return m_CurPart;
}

void DEPartCollection::FileNew()
{
    if(m_CurPart)
    {
        delete m_CurPart;
        m_CurPart = nullptr;
    }
    m_CurPart = new DEPart();
}
void DEPartCollection::FileOpen(QDomDocument* doc)
{
    if(m_CurPart)
    {
        delete m_CurPart;
        m_CurPart = nullptr;
    }

    m_CurPart = new DEPart(doc);
}
void DEPartCollection::FileSave(QString FileName)
{
    QFile file(FileName);
    if (!file.open(QFileDevice::ReadWrite | QFileDevice::Truncate))
    {
        return;
    }

    QTextStream stream(&file);
    m_CurPart->GetXml()->save(stream, 4);		// 缩进四格
    file.close();

    m_CurPart->SetSaved(true);
}
void DEPartCollection::FileDelete()
{
    if(m_CurPart)
    {
        delete m_CurPart;
        m_CurPart = nullptr;
    }
}
