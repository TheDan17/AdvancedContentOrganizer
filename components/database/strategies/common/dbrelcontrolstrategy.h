#ifndef DBRELCONTROLSTRATEGY_H
#define DBRELCONTROLSTRATEGY_H

#include <vector>
#include <string>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "../../../../utils/resulthandler.h"

class DBRelControlStrategy {
public:
    virtual Result<> select_table(std::string table_name);
    virtual Result<QSqlTableModel*> get_table(std::string table_name);
    virtual Result<std::vector<QSqlRecord>> execQuery(QSqlQuery query, bool is_transaction);
    virtual Result<std::vector<std::vector<QSqlRecord>>> execQueries(std::vector<QSqlQuery> queries, bool is_transactioning);
    virtual Result<> rollback();
    virtual Result<> commit();

    virtual void create();
    virtual void read();
    virtual void update();
    virtual void remove();

    virtual QSqlDatabase& get_db_link();
};

#endif // DBRELCONTROLSTRATEGY_H
