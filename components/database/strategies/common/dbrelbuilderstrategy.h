#ifndef DBRELBUILDERSTRATEGY_H
#define DBRELBUILDERSTRATEGY_H

#include <QSqlQuery>

#include "dbrelpack.h"
#include "../../tables.h"
#include "../../dbconfig.h"
#include "../../../../utils/resulthandler.h"

class DBRelBuilderStrategy {
public:
    virtual Result<> add_table(std::string table_name, QSqlQuery table_query);
    virtual Result<> add_table(DBTablePrototype table_prototype);
    virtual Result<> make_tables();
    virtual DBRelPack* release_core();
};

#endif // DBRELBUILDERSTRATEGY_H
