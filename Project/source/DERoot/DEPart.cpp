#include "DEPart.h"

DEPart::DEPart()
{
    b_Saved = true;
    m_Xml = new QDomDocument;

    // 创建XML处理类，通常用于处理第一行描述信息
    QDomProcessingInstruction instruction;

    // 创建XML头部格式
    instruction = m_Xml->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");

    // 添加到XML文件中
    m_Xml->appendChild(instruction);

    // 创建根节点
    QDomElement root = m_Xml->createElement("DEDialog");
    m_Xml->appendChild(root);
}

DEPart::DEPart(QDomDocument* doc)
{
    b_Saved = true;
    m_Xml = doc;

    //将XML中的BlockID加入记录
    QDomElement root = m_Xml->documentElement();
    ReadNodeChildrenID(root);
}

DEPart::~DEPart()
{

}

QString DEPart::GetAutoBlockID(QString type)
{
    int size = m_BlockIDs.size();
    int temp = size;
    QString name = type + QString::number(temp);
    while(m_BlockIDs.find(name) != m_BlockIDs.end())
    {
        temp++;
        name = type + QString::number(temp);
    }
    m_BlockIDs.insert(name);
    return name;
}

void DEPart::SetSaved(bool bSave)
{
    b_Saved = bSave;
}

void DEPart::ReadNodeChildrenID(QDomElement parent)
{
    if(parent.hasChildNodes())
    {
        for(int i=0; i<parent.childNodes().size(); i++)
        {
            QDomElement e = parent.childNodes().at(i).toElement();
            m_BlockIDs.insert(e.tagName());
            ReadNodeChildrenID(e);
        }
    }
}
