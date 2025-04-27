#include "dbrelbuildermysql.h"

#include "../../../../main/globalinstances.h"

std::vector<std::string> QStringList_to_VectorString(const QList<QString>& qlist) {
    std::vector<std::string> result(qlist.size());
    for (int i=0; i<qlist.size(); i++) {
        result[i] = qlist.at(i).toUtf8().data();
    }
    return result;
}
#include <QStringList>
#include <QCoreApplication>
#include <QSqlError>
#include <QMessageBox>
DBRelBuilderMySQL::DBRelBuilderMySQL(dbConfig* config) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(config->dbName.c_str());
    db.setHostName(config->dbHost.c_str());
    db.setUserName(config->dbUser.c_str());
    db.setPassword(config->dbPassword.c_str());
    bool is_db_open = db.open();
    global::logger()->log_msg(DEBUG, "Database opened: "+std::to_string(is_db_open));
    if (!is_db_open){
        std::string err = std::string(db.lastError().text().toLocal8Bit().data());
        global::logger()->log_msg(ERROR, "Database open error: "+err);
        QMessageBox::critical(nullptr, "Ошибка", err.c_str());
    }
    this->db_t = std::move(db);
}

Result<> DBRelBuilderMySQL::add_table(std::string table_name, QSqlQuery table_query){
    if (this->is_released)
        return error("Core released, builder strategy methods unavaliable");

    this->tables.push_back(std::make_pair(std::move(table_name), std::move(table_query)));
    return value();
}
Result<> DBRelBuilderMySQL::add_table(DBTablePrototype table_prototype){
    if (this->is_released)
        return error("Core released, builder strategy methods unavaliable");

    this->tables.push_back(table_prototype);
    return value();
}

Result<> DBRelBuilderMySQL::make_tables(){
    if (this->is_released)
        return error("Core released, builder strategy methods unavaliable");

    QSqlTableModel* model;
    for (auto& tablename : this->tables){
        model = new QSqlTableModel(nullptr, this->db_t);

        std::string table_name;
        std::visit([&table_name](auto& arg){
            if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, DBTablePrototype>) {
                table_name = arg.get_name();
            } else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::pair<std::string, QSqlQuery>>) {
                table_name = arg.first;
                bool result = arg.second.exec(); // todo if !result, add to error query, which be displayed after init or after start
            }
        }, tablename);

        this->table_names.push_back(table_name);
        model->setTable(table_name.c_str());

        bool is_selected = model->select();
        if (is_selected) {
            this->table_models.push_back(model);
        } else {
            delete model;
            this->table_models.push_back(nullptr);
        }
    }
    return value();
}

DBRelPackMySQL* DBRelBuilderMySQL::release_core(){
    this->is_released = true;
    return new DBRelPackMySQL(std::move(this->db_t),
                              std::move(this->table_names),
                              std::move(this->table_models));
}
