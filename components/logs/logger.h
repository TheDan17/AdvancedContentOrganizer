#ifndef LOGGER_H
#define LOGGER_H

#include <filesystem>
#include <fstream>
#include <string>

#include "logdata.h"


extern std::string str_levels[4];
extern std::filesystem::path last_log_path;

class Logger {
private:
    enum LogLevel logfile_min_lvl;
    std::filesystem::path logfile_path;
    std::ofstream logfile_stream = nullptr;
    void log_start_msg();
public:
    Logger(enum LogLevel min_log_lvl = INFO, std::filesystem::path log_path = "logs/");
    ~Logger();
    void log_msg(LogData data);
    void log_msg(enum LogLevel lvl, std::string msg, std::string component = "");//__builtin_FUNCTION());
    void log_error(std::string first_part, std::runtime_error error);
    void set_log_lvl(enum LogLevel new_lvl);
};

#endif // LOGGER_H
