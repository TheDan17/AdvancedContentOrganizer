#ifndef DATABASEREL_H
#define DATABASEREL_H

#include <QSqlDatabase>

#include "strategies/common/dbrelcontrolstrategy.h"

class DBRelInstance {
private:
    QSqlDatabase& db;
public:
    DBRelControlStrategy* action;
    DBRelInstance(QSqlDatabase &db_obj, DBRelControlStrategy* strategy);
};

#endif // DATABASEREL_H
