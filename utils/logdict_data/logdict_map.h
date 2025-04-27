#include "logdict_enum.h"

#include <map>
#include <string>

#ifndef LOGDICT_MAP_H
#define LOGDICT_MAP_H

extern const std::map<Msg::init, std::string> msg_init_data;
extern const std::map<Msg::error, std::string> msg_error_data;
extern const std::map<Msg::prog_ui, std::string> msg_prog_ui;

#endif // LOGDICT_MAP_H
