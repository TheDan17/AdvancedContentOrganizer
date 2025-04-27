#include "logdict_data/logdict_enum.h"
#include "logdict_data/logdict_map.h"

#ifndef LOGDICT_H
#define LOGDICT_H

class LogDict {
public:
    static std::string getMsg(enum Msg::init init);
    static std::string getMsg(enum Msg::error error);
    static std::string getMsg(enum Msg::prog_ui prog_ui);
};

#endif // LOGDICT_H
