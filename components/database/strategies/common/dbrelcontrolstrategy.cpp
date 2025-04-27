#include "dbrelcontrolstrategy.h"

Result<> DBRelControlStrategy::select_table(std::string table_name){return value();}
Result<QSqlTableModel*> DBRelControlStrategy::get_table(std::string table_name){return Result<QSqlTableModel*>(nullptr);}
Result<std::vector<QSqlRecord>> DBRelControlStrategy::execQuery(QSqlQuery query, bool is_transaction){}
Result<std::vector<std::vector<QSqlRecord>>> DBRelControlStrategy::execQueries(std::vector<QSqlQuery> queries, bool is_transactioning){}
Result<> DBRelControlStrategy::rollback(){return value();}
Result<> DBRelControlStrategy::commit(){return value();}
void DBRelControlStrategy::create(){}
void DBRelControlStrategy::read(){}
void DBRelControlStrategy::update(){}
void DBRelControlStrategy::remove(){}
QSqlDatabase& DBRelControlStrategy::get_db_link(){}
