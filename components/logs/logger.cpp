#include "logger.h"

#include "../../utils/strdict.h"

std::string str_levels[4] = {"Debug", "Info", "Warning", "Error"};
const int MAX_STR_LEVELS=9;
std::filesystem::path last_log_path = "";

std::string loglevel_to_str(enum LogLevel lvl){
    return str_levels[(int)lvl];
}
Logger::Logger(enum LogLevel min_log_lvl, std::filesystem::path log_path) :
    logfile_min_lvl(min_log_lvl), logfile_path(log_path) {

    std::string log_filename = DatetimeUtils::get_formatted_now(FILENAME) + ".txt";
    this->logfile_path = this->logfile_path.append(log_filename);
    std::filesystem::create_directory(this->logfile_path.parent_path());
    last_log_path = this->logfile_path;

    logfile_stream.open(logfile_path, std::ios::out);
    log_start_msg();
}
Logger::~Logger(){
    log_msg(DEBUG, "Final message: Logger destructor invoked");
    logfile_stream.close();
}

void Logger::log_start_msg(){
    this->logfile_stream << "Log of ' " << str::Info::AppName << " ' program" << " "
                         << "(version " << str::Info::AppVersion << ")" << "\n";
}

void Logger::log_msg(LogData data){
    if(logfile_stream && (data.level >= logfile_min_lvl)){
        // time
        logfile_stream << "[" << DatetimeUtils::format_datetime(data.point, STANDART) << "]" << " ";
        // level
        logfile_stream << std::left << std::setw(MAX_STR_LEVELS)
                       << "[" + loglevel_to_str(data.level) + "]" << " ";
        // message
        logfile_stream << data.message << " ";
        // component
        if (!data.component.empty())
            logfile_stream << "(" << data.component << ")";
        // end
        logfile_stream << std::endl;
        std::flush(this->logfile_stream);
    }
}

void Logger::log_msg(enum LogLevel lvl, std::string msg, std::string component){
    log_msg(std::move(LogData(DatetimeUtils::get_now(), lvl, msg, component)));
}
void Logger::log_error(std::string first_part, std::runtime_error error){
    std::string err_text = error.what();
    std::string msg = first_part + err_text;
    log_msg(std::move(LogData(DatetimeUtils::get_now(), ERROR, msg, "")));
}
