#ifndef LOGDATA_H
#define LOGDATA_H

#include <chrono>
#include <string>

#include "../../utils/datetimeutils.h"

enum LogLevel{ DEBUG, INFO, WARNING, ERROR };

class LogData {
public:
    timepoint point;
    enum LogLevel level;
    std::string message;
    std::string component;
    LogData(timepoint p, enum LogLevel lvl, std::string msg, std::string cmp);
};

#endif // LOGDATA_H
