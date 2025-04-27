#ifndef DBRELPACK_H
#define DBRELPACK_H

#include <QSqlDatabase>

class DBRelPack {
public:
    virtual QSqlDatabase release_main_core();
};

#endif // DBRELPACK_H
