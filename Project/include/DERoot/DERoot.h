#ifndef DEROOT_H
#define DEROOT_H

#include "DERoot_global.h"
#include <mutex>

class DEPartCollection;
class DECmdCollection;

class DEROOT_EXPORT DERoot
{
private:
    DERoot();
    ~DERoot();

public:
    static DERoot* GetDERoot();
    static void deleteDERoot();

public:
    DEPartCollection* GetPartCollection();

private:
    static DERoot *m_Root;
    static std::mutex m_Mutex;

private:
    DEPartCollection* m_PartCollection;
    DECmdCollection* m_CmdCollection;

//private:
//    int i_FileMajorVer;               //文件大版本号
//    int i_FileMinorVer;               //文件小版本号
};

#endif // DEROOT_H
