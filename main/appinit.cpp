#include "appinit.h"

AppInit::AppInit(Logger* logger) {
    logger->log_msg(INFO, "'Logger' pointer sended to 'AppInit'.");
    global::add_one(LOGGER, logger);
    this->temp_logger = logger;
}

Result<InstancesPack*> AppInit::init_all(){
    InstancesPack* ip = new InstancesPack();

    auto init_logger_result = this->init_logger();
    if (init_logger_result.is_ok())
        ip->setInstance(LOGGER, init_logger_result.value());

    auto init_dbrel_result = this->init_dbrel();
    if (init_dbrel_result.is_ok()) {
        ip->setInstance(DBREL, init_dbrel_result.value());
        global::logger()->log_msg(INFO, "Relational DB fully inited! (AppManagerInit)");
    } else {
        global::logger()->log_error("Failed DB init: ", init_dbrel_result.error());
    }

    global::logger()->log_msg(INFO, "Initing globalization ended! (AppManagerInit)");

    return value(ip);
}

Result<Logger*> AppInit::init_logger(){
    Logger* logger;
    if (this->temp_logger == nullptr){
        logger = new Logger();
        logger->log_msg(DEBUG, "Create Logger (AppManagerInit::init_logger)");
    } else {
        logger = this->temp_logger;
        logger->log_msg(DEBUG, "Logger found, return ptr (init_logger)");
    }
    return value(logger);
}

std::string db_name = "CWLibraryDB";
std::string servers_query = \
    "CREATE TABLE IF NOT EXISTS servers (\n"
    "local_id INTEGER AUTO_INCREMENT PRIMARY KEY,\n"
    "uuid VARCHAR(36) NOT NULL UNIQUE,\n"
    "is_your BOOLEAN NOT NULL DEFAULT FALSE,\n"
    "host_uuid VARCHAR(36) NOT NULL,\n"
    "items_amount INTEGER NOT NULL DEFAULT 0\n"
    ");";
std::string your_servers_privacy_query = \
    "CREATE TABLE IF NOT EXISTS your_servers_privacy (\n"
    "id INTEGER PRIMARY KEY,\n"
    "visibility ENUM('BY_HOST', 'BY_NAME', 'BY_PASSWORD') NOT NULL DEFAULT 'BY_NAME',\n"
    "password_hash VARCHAR(255),\n"
    "password_salt VARCHAR(255),\n"
    "UNIQUE KEY (password_hash, password_salt),\n"
    "FOREIGN KEY (id) REFERENCES servers(local_id)\n"
    ");";
std::string servers_info_query = \
    "CREATE TABLE IF NOT EXISTS servers_info (\n"
    "id INTEGER PRIMARY KEY,\n"
    "name VARCHAR(32) NOT NULL,\n"
    "description VARCHAR (255),\n"
    "last_active DATETIME,\n"
    "FOREIGN KEY (id) REFERENCES servers(local_id)\n"
    ");";
std::string servers_items_query = \
    "CREATE TABLE IF NOT EXISTS servers_items (\n"
    "item_local_id INTEGER AUTO_INCREMENT PRIMARY KEY,\n"
    "server_id INTEGER NOT NULL,\n"
    "item_server_id INTEGER NOT NULL,\n"
    "UNIQUE KEY (server_id, item_server_id),\n"
    "FOREIGN KEY (server_id) REFERENCES servers(local_id)\n"
    ");";
std::string items_data_query = \
    "CREATE TABLE IF NOT EXISTS items_data (\n"
    "id INTEGER PRIMARY KEY,\n"
    "name VARCHAR(64),\n"
    "kind ENUM('FILE', 'DIRECTORY') NOT NULL DEFAULT 'DIRECTORY',\n"
    "parent_item INTEGER NOT NULL DEFAULT -1,\n"
    "location ENUM('DISK', 'CLOUD') NOT NULL,\n"
    "destination VARCHAR (255)\n"
    //"FOREIGN KEY (id) REFERENCES servers_items(item_local_id),\n"
    //"FOREIGN KEY (parent_item) REFERENCES items_data(id) ON DELETE SET DEFAULT\n"
    ");";
std::string items_metadata_query = \
    "CREATE TABLE IF NOT EXISTS items_metadata (\n"
    "id INT PRIMARY KEY,\n"
    "created DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,\n"
    "last_edited DATETIME,\n"
    "FOREIGN KEY (id) REFERENCES servers_items(item_local_id)\n"
    ");";

#include "../components/database/databaserel.h"
#include "../components/database/dbrelbuilder.h"
#include "../components/database/strategies/mysql/dbrelbuildermysql.h"
#include "../components/database/strategies/mysql/dbrelcontrolmysql.h"

Result<DBRelInstance*> AppInit::init_dbrel(){
    std::vector<std::string> tables, queries;
    tables.push_back("servers"); queries.push_back(servers_query);
    tables.push_back("your_servers_privacy"); queries.push_back(your_servers_privacy_query);
    tables.push_back("servers_info"); queries.push_back(servers_info_query);
    tables.push_back("servers_items"); queries.push_back(servers_items_query);
    tables.push_back("items_data"); queries.push_back(items_data_query);
    tables.push_back("items_metadata"); queries.push_back(items_metadata_query);

    dbConfig* config = new dbConfig("localhost", "CWLProg", "3321", "cwlibrarydb");
    DBRelBuilderMySQL* b = new DBRelBuilderMySQL(config);
    DBRelBuilder builder(b, dbc_mysql_factory);
    for (int i = 0; i < tables.size(); ++i){
        QSqlQuery table_query;
        table_query.prepare(queries[i].c_str());
        builder.add_table(tables[i], std::move(table_query));
    }
    builder.create_tables();
    return builder.create_db();
}

