#include "logdict.h"

std::string LogDict::getMsg(Msg::init init_enum){
    return msg_init_data.at(init_enum);
}
std::string LogDict::getMsg(Msg::error error_enum){
    return msg_error_data.at(error_enum);
}
std::string LogDict::getMsg(enum Msg::prog_ui prog_ui_enum){
    return msg_prog_ui.at(prog_ui_enum);
}
