#ifndef DBRELBUILDERMYSQL_H
#define DBRELBUILDERMYSQL_H

#include <string>
#include <vector>
#include <variant>
#include <utility>
#include <QSqlQuery>
#include <QSqlDatabase>

#include "dbrelpackmysql.h"
#include "../common/dbrelbuilderstrategy.h"
#include "../../tables.h"
#include "../../dbconfig.h"
#include "../../../../utils/resulthandler.h"

class DBRelBuilderMySQL : public DBRelBuilderStrategy {
private:
    bool is_released = false;
    QSqlDatabase db_t;
    std::vector<std::variant<DBTablePrototype, std::pair<std::string, QSqlQuery>>> tables;
    std::vector<std::string> table_names;
    std::vector<QSqlTableModel*> table_models;
public:
    DBRelBuilderMySQL(dbConfig* config);
    Result<> add_table(std::string table_name, QSqlQuery table_query);
    Result<> add_table(DBTablePrototype table_prototype);
    Result<> make_tables();
    DBRelPackMySQL* release_core();
};

#endif // DBRELBUILDERMYSQL_H
