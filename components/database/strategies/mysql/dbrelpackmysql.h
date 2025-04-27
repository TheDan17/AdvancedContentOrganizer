#ifndef DBRELPACKMYSQL_H
#define DBRELPACKMYSQL_H

#include <vector>
#include <string>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "../common/dbrelpack.h"

class DBRelPackMySQL : public DBRelPack {
public:
    QSqlDatabase db;
    std::vector<std::string> table_names;
    std::vector<QSqlTableModel*> table_models;
    DBRelPackMySQL(QSqlDatabase db_arg,
                   std::vector<std::string> tnames,
                   std::vector<QSqlTableModel*> tmodels);

    QSqlDatabase release_main_core();
};

#endif // DBRELPACKMYSQL_H
