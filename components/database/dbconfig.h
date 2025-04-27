#ifndef DBCONFIG_H
#define DBCONFIG_H

#include <string>

class dbConfig {
public:
    std::string dbHost;
    std::string dbUser;
    std::string dbPassword;
    std::string dbName;
    dbConfig(std::string host, std::string user,
             std::string pass, std::string name);
};

#endif // DBCONFIG_H
