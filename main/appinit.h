#ifndef APPINIT_H
#define APPINIT_H

#include "globalinstances.h"
#include "../utils/resulthandler.h"
#include "../components/logs/logger.h"
#include "../components/database/databaserel.h"

class AppInit {
private:
    Logger* temp_logger;
public:
    AppInit(Logger* logger = nullptr);
    Result<InstancesPack*> init_all();
    Result<Logger*> init_logger();
    Result<DBRelInstance*> init_dbrel();
};

#endif // APPINIT_H
