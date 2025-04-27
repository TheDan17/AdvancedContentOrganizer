#ifndef DBRELCONTROLMYSQL_H
#define DBRELCONTROLMYSQL_H

#include <vector>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>

#include "../common/dbrelcontrolstrategy.h"
#include "dbrelpackmysql.h"

class DBRelControlMySQL : public DBRelControlStrategy {
private:
    QSqlDatabase db;
    std::vector<QSqlTableModel*> db_tables;
    int current_table_i = -1;
    bool is_transactioning = false;
public:
    std::vector<std::string> db_tablenames; // TODO costyl

    DBRelControlMySQL(DBRelPackMySQL* core);
    Result<> select_table(std::string table_name);
    Result<QSqlTableModel*> get_table(std::string table_name);
    Result<std::vector<QSqlRecord>> execQuery(QSqlQuery query, bool is_transaction = false);
    Result<std::vector<std::vector<QSqlRecord>>> execQueries(std::vector<QSqlQuery> queries, bool is_transactioning = false);
    Result<> rollback();
    Result<> commit();
    // CRUD
    void create();
    void read();
    void update();
    void remove();

    QSqlDatabase& get_db_link();
};

extern std::function<DBRelControlStrategy*(DBRelPack*)> dbc_mysql_factory;

#endif // DBRELCONTROLMYSQL_H
