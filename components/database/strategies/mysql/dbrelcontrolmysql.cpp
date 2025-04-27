#include "dbrelcontrolmysql.h"

DBRelControlMySQL::DBRelControlMySQL(DBRelPackMySQL* core) {
    this->db = std::move(core->db);
    this->db_tablenames = std::move(core->table_names);
    this->db_tables = std::move(core->table_models);
}

#include <algorithm>
Result<> DBRelControlMySQL::select_table(std::string table_name){
    auto it = std::find(db_tablenames.begin(), db_tablenames.end(), table_name);
    if (it == db_tablenames.end())
        return error("No such table in database");
    this->current_table_i = it - db_tablenames.begin();
    return value();
}

Result<QSqlTableModel*> DBRelControlMySQL::get_table(std::string table_name){
    auto select_result = this->select_table(table_name);
    if (select_result.is_ok())
        return Result<QSqlTableModel*>(this->db_tables.at(current_table_i));
    else
        return Result<QSqlTableModel*>(select_result.error());
}

std::function<DBRelControlStrategy*(DBRelPack*)> dbc_mysql_factory = [](DBRelPack* pack){
    return new DBRelControlMySQL((DBRelPackMySQL*)pack);
};

Result<std::vector<QSqlRecord>> DBRelControlMySQL::execQuery(QSqlQuery query, bool is_transaction){
    auto exec_result = execQueries({std::move(query)}, is_transaction);
    if (exec_result.is_ok()){
        return exec_result.value()[0];
    } else {
        return exec_result.error();
    }
}
#include <QSqlError>
using exec_error = Result<std::vector<std::vector<QSqlRecord>>>;
Result<std::vector<std::vector<QSqlRecord>>> DBRelControlMySQL::execQueries(std::vector<QSqlQuery> queries, bool is_transaction){
    if (!is_transaction && this->is_transactioning) {
        return exec_error(std::runtime_error("Cannot interrupt transaction"));
    }
    if (is_transaction && !this->is_transactioning){
        auto is_transaction_success = this->db.transaction();
        if (is_transaction_success)
            this->is_transactioning = true;
        else
            return exec_error(std::runtime_error("Failed start transaction"));
    }

    if (this->is_transactioning){
        auto is_savepoint_created = QSqlQuery("SAVEPOINT sp", this->db).exec();
        if (!is_savepoint_created)
            return exec_error(std::runtime_error("Failed to start executing queries"));
    }

    std::vector<std::vector<QSqlRecord>> queries_results;
    for (int i = 0; i < queries.size(); i++){
        auto& query = queries[i];
        auto is_exec_success = query.exec();
        //QSqlQuery query(queries[i].lastQuery(), this->db);
        //auto is_exec_success = query.exec();
        QString debugstr = query.executedQuery();
        if (is_exec_success) {
            std::vector<QSqlRecord> query_results;
            while(query.next())
                query_results.push_back(query.record());
            queries_results.push_back(std::move(query_results));
        } else {
            if (this->is_transactioning) {
                QSqlQuery("ROLLBACK TO sp", this->db).exec();
                std::runtime_error text("Query #"+std::to_string(i)+" failed. Sequence of queries canceled");
                return exec_error(text);
            } else {
                std::runtime_error text("Query #"+std::to_string(i)+" failed. Error: "+ query.lastError().text().toStdString());
                return exec_error(text);
            }
        }
    }

    if (this->is_transactioning)
        QSqlQuery("RELEASE SAVEPOINT sp", this->db).exec();

    return value(std::move(queries_results));
}

#include <QSqlError>
Result<> DBRelControlMySQL::rollback(){
    auto is_success = this->db.rollback();
    if (is_success) {
        this->is_transactioning = false;
        return value();
    } else {
        return error(db.lastError().text().toLocal8Bit().data());
    }
}
Result<> DBRelControlMySQL::commit(){
    auto is_success = this->db.commit();
    if (is_success) {
        this->is_transactioning = false;
        return value();
    } else {
        return error(db.lastError().text().toLocal8Bit().data());
    }
}

void DBRelControlMySQL::create(){}
void DBRelControlMySQL::read(){}
void DBRelControlMySQL::update(){}
void DBRelControlMySQL::remove(){}

QSqlDatabase& DBRelControlMySQL::get_db_link(){return db;}
