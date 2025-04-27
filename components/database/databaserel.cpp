#include "databaserel.h"

DBRelInstance::DBRelInstance(QSqlDatabase &db_obj, DBRelControlStrategy* strategy) : db(db_obj) {
    this->action = strategy;
}
