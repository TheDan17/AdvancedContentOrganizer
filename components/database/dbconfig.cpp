#include "dbconfig.h"

dbConfig::dbConfig(std::string host, std::string user,
                   std::string pass, std::string name) {
    this->dbHost = host;
    this->dbUser = user;
    this->dbPassword = pass;
    this->dbName = name;
}
