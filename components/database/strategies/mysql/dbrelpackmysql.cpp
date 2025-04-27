#include "dbrelpackmysql.h"

DBRelPackMySQL::DBRelPackMySQL(QSqlDatabase db_arg,
                               std::vector<std::string> tnames,
                               std::vector<QSqlTableModel*> tmodels){
    this->db = std::move(db_arg);
    this->table_names = std::move(tnames);
    this->table_models = std::move(tmodels);
}

QSqlDatabase DBRelPackMySQL::release_main_core(){
    return std::move(this->db);
}
