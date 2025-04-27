#ifndef GLOBALINSTANCES_H
#define GLOBALINSTANCES_H

#include <map>

#include "../components/logs/logger.h"
#include "../components/database/databaserel.h"
#include "../components/network/transfer/filenetworktransfer.h"

enum Instances{ LOGGER, DBREL, FILENET, TEST };

class GlobalInstances;
class InstancesPack{
    friend class GlobalInstances;
private:
    std::map<enum Instances, void*> ptrs;
public:
    InstancesPack();
    void setInstance(enum Instances i, void* ptr);
    void* getInstance(enum Instances i);
};

class GlobalInstances {
private:
    static std::map<enum Instances, void*> ptrs;
public:
    static void add_instances(InstancesPack* ip);
    static void update_instances(InstancesPack* ip);
    static void delete_instances();

    static void add_one(enum Instances i, void* ptr);

    static void* getInstance(enum Instances i);
    static Logger* logger();
    static DBRelInstance* dbrel();
    static FileNetworkTransfer* filenet();
};

using global = GlobalInstances;

#endif // GLOBALINSTANCES_H
