#include "tables.h"

DBTablePrototype::DBTablePrototype(std::string local_name){
    this->name = local_name;
}
std::string DBTablePrototype::get_name(){
    return this->name;
}
