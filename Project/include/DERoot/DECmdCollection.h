#ifndef DECMDCOLLECTION_H
#define DECMDCOLLECTION_H

#include "DERoot.h"
#include "DECmd.h"
#include <map>
/**
 * @brief 命令管理类
 */
class DEROOT_EXPORT DECmdCollection
{
public:
    DECmdCollection(DERoot* root);

    typedef int(DECmdCollection::*DEPFN)(void* para);

    void OnCmdResponse(int ID);
    void FindPfnFromCmd(int iCmdID, DEPFN& pfn);
    void SetupCmd();

private:
    DERoot* m_root;
    std::map<int, DEPFN> m_CmdCollector;

public:
    int FileNew(void* para);
};

#endif // DECMDCOLLECTION_H
