#include "DERoot.h"
#include "DEPartCollection.h"
#include "DECmdCollection.h"

DERoot *DERoot::m_Root = nullptr;
std::mutex DERoot::m_Mutex;

//版本号
const int Proj_Version_major = 1;
const int Proj_Version_minor = 1;

DERoot* DERoot::GetDERoot()
{
    if(m_Root == nullptr)
    {
        std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
        if (m_Root == nullptr)
        {
            volatile auto temp = new (std::nothrow) DERoot();
            m_Root = temp;
        }
    }
    return m_Root;
}

void DERoot::deleteDERoot()
{
    std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
    if (m_Root)
    {
        delete m_Root;
        m_Root = nullptr;
    }
}

DERoot::DERoot()
{
    m_PartCollection = new DEPartCollection(this);
    m_CmdCollection = new DECmdCollection(this);
}

DERoot::~DERoot()
{
    if(m_PartCollection)
    {
        delete m_PartCollection;
        m_PartCollection = nullptr;
    }
    if(m_CmdCollection)
    {
        delete m_CmdCollection;
        m_CmdCollection = nullptr;
    }
}

DEPartCollection* DERoot::GetPartCollection()
{
    return m_PartCollection;
}
