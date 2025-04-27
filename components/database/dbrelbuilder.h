#ifndef DBRELBUILDER_H
#define DBRELBUILDER_H

#include <string>
#include <QSqlQuery>

#include "dbconfig.h"
#include "databaserel.h"
#include "tables.h"
#include "strategies/common/dbrelbuilderstrategy.h"
#include "strategies/common/dbrelcontrolstrategy.h"
#include "strategies/common/dbrelpack.h"
#include "../../utils/resulthandler.h"


class DBRelBuilder {
private:
    DBRelBuilderStrategy* build_strategy;
    DBRelControlStrategy* control_strategy;
    std::function<DBRelControlStrategy*(DBRelPack*)> control_factory;
public:
    DBRelBuilder(DBRelBuilderStrategy* builder,
                 std::function<DBRelControlStrategy*(DBRelPack*)> factory,
                 dbConfig* config = nullptr);
    Result<> add_table(std::string table_name, QSqlQuery table_query);
    Result<> add_table(DBTablePrototype table_prototype);
    Result<> create_tables();
    Result<DBRelInstance*> create_db();
};

#endif // DBRELBUILDER_H
