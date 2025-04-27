#include "globalinstances.h"

void* getMapSafe(std::map<enum Instances, void*> ptrs, enum Instances i){
    if (ptrs.find(i) != std::end(ptrs))
        return ptrs.at(i);
    else
        return nullptr;
}

// INSTANCES PACK

InstancesPack::InstancesPack(){}
void InstancesPack::setInstance(enum Instances i, void* ptr){
    this->ptrs[i] = ptr;
}
void* InstancesPack::getInstance(enum Instances i){
    return getMapSafe(this->ptrs, i);
}

// GLOBAL INSTANCES

std::map<enum Instances, void*> GlobalInstances::ptrs;

void GlobalInstances::add_instances(InstancesPack* ip){
    for(const auto& [key, value] : ip->ptrs){
        auto r = GlobalInstances::ptrs.find(key);
        if (r == std::end(GlobalInstances::ptrs) ){// || GlobalInstances::ptrs.at(r) == nullptr) {
            GlobalInstances::ptrs[key] = value;
        }
    }
}
void GlobalInstances::update_instances(InstancesPack* ip){
    for(const auto& [key, value] : ip->ptrs){
        GlobalInstances::ptrs[key] = value;
    }
}
void GlobalInstances::delete_instances(){
    for(const auto& [key, value] : GlobalInstances::ptrs){
        if (value != nullptr) {
            switch(key){
            case LOGGER:
                delete (Logger*)value; break;
            case DBREL:
                delete (DBRelInstance*)value; break;
            case FILENET:
                delete (FileNetworkTransfer*)value; break;
            case TEST:
                break;//delete (TestMain*)value; break;
            }
        }
    }
}

void GlobalInstances::add_one(enum Instances i, void* ptr){
    InstancesPack* ip = new InstancesPack();
    ip->setInstance(i, ptr);
    global::update_instances(ip);
    delete ip;
}

void* GlobalInstances::getInstance(enum Instances i){
    return getMapSafe(GlobalInstances::ptrs, i);
}
Logger* GlobalInstances::logger(){
    return (Logger*)getMapSafe(GlobalInstances::ptrs, LOGGER);
}
DBRelInstance* GlobalInstances::dbrel(){
    return (DBRelInstance*)getMapSafe(GlobalInstances::ptrs, DBREL);
}
FileNetworkTransfer* GlobalInstances::filenet(){
    return (FileNetworkTransfer*)getMapSafe(GlobalInstances::ptrs, FILENET);
}
