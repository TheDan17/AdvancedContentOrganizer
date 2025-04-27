#include "logdata.h"

LogData::LogData(timepoint p, enum LogLevel lvl, std::string msg, std::string cmp) {
    this->point = p;
    this->level = lvl;
    this->message = msg;
    this->component = cmp;
}
