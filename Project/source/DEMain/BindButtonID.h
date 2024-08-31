#ifndef BINDBUTTONID_H
#define BINDBUTTONID_H

#include <QObjectUserData>

class User : public QObjectUserData
{
public:
    int nID;
    QString name;

    User()
    {
        nID = 0;
        name = "";
    }
    User(const User & sour)
    {
        nID = sour.nID;
        name = sour.name;
    }
};

#endif // BINDBUTTONID_H
