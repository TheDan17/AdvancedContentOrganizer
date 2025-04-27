#include "appmanager.h"

/*AppManager::AppManager() {

}
AppManager::~AppManager() {

}
*/


//#include <vector>
//bool AppManager::init_global_instances() {
    //std::vector<ResultPtr<void>> return_values;
    //ResultPtr<Logger> logger = init_log();
    /*if (logger.is_success()) {
        //return_values.push_back(init_rel_db());
        //return_values.push_back(init_norel_db());
        //return_values.push_back(init_reqh());

        for (auto ptr : return_values){
            if (!ptr.is_success())
                logger.get_value()->log_msg(ptr.get_error().what(), ERROR);
        }
    } else {
        throw std::runtime_error("Logger doesn't start - Fatal error");
        return false;
    }
*/
//    return true;
//}
/*
ResultPtr<Logger> AppManager::init_log(){
    Logger* logger = new Logger();
    return ResultPtr<Logger>(logger);
}
ResultPtr<DBRelInstance> AppManager::init_rel_db(){
    return ResultPtr<DBRelInstance>(nullptr);
}
ResultPtr<DBNoRelInstance> AppManager::init_norel_db(){
    return ResultPtr<DBNoRelInstance>(nullptr);
}
ResultPtr<RequestService> AppManager::init_reqh(){
    return ResultPtr<RequestService>(nullptr);
}

*/
