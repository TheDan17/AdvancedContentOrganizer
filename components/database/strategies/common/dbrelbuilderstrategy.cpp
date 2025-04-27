#include "dbrelbuilderstrategy.h"

Result<> DBRelBuilderStrategy::add_table(std::string table_name, QSqlQuery table_query){return value();}
Result<> DBRelBuilderStrategy::add_table(DBTablePrototype table_prototype){return value();}
Result<> DBRelBuilderStrategy::make_tables(){return value();}
DBRelPack* DBRelBuilderStrategy::release_core(){return nullptr;}
