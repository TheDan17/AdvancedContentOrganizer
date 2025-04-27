#include "dbrelbuilder.h"

DBRelBuilder::DBRelBuilder(DBRelBuilderStrategy* builder,
                           std::function<DBRelControlStrategy*(DBRelPack*)> factory,
                           dbConfig* config) {
    this->build_strategy = builder;
    this->control_factory = factory;
}
Result<> DBRelBuilder::add_table(std::string table_name, QSqlQuery table_query){
    return this->build_strategy->add_table(table_name, std::move(table_query));
}
Result<> DBRelBuilder::add_table(DBTablePrototype table_prototype){
    return this->build_strategy->add_table(std::move(table_prototype));
}
Result<> DBRelBuilder::create_tables(){
    return this->build_strategy->make_tables();
}
Result<DBRelInstance*> DBRelBuilder::create_db(){
    DBRelPack* dbpack = this->build_strategy->release_core();
    this->control_strategy = this->control_factory(dbpack);
    DBRelInstance* db = new DBRelInstance(this->control_strategy->get_db_link(), this->control_strategy);
    return value(db);
}
