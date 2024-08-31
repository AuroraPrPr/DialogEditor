#include "DECmdCollection.h"
#include <utility>

DECmdCollection::DECmdCollection(DERoot* root)
{
    m_root = root;
    SetupCmd();
}

void DECmdCollection::SetupCmd()
{
    m_CmdCollector = {
        {ID_DE_FILE_NEW, &DECmdCollection::FileNew}
    };
}

void DECmdCollection::OnCmdResponse(int ID)
{
    DEPFN pfn = NULL;
    auto it = m_CmdCollector.find(ID);
    if(it != m_CmdCollector.end())
    {
        pfn = it->second;
        (this->*pfn)(nullptr);
    }
}

void DECmdCollection::FindPfnFromCmd(int iCmdID, DEPFN& pfn)
{

}

int DECmdCollection::FileNew(void* para)
{
    return 0;
}
