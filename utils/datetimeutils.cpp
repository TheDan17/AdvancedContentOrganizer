#include "datetimeutils.h"

#include <sstream>
#include <iomanip>

std::string get_format_string(enum timeformat tf){
    switch (tf){
    case FILENAME:
        return "%d_%m_%Y %H-%M-%S";
    case STANDART:
        return "%d.%m.%Y %H:%M:%S";
    default:
        return "";
    }
}
std::string DatetimeUtils::format_datetime(timepoint p, enum timeformat tf){
    std::string format = get_format_string(tf);
    if (format.empty())
        return "";
    const std::time_t now_t = std::chrono::system_clock::to_time_t(p);
    std::stringstream timestream;
    timestream << std::put_time(std::localtime(&now_t), format.c_str());
    return timestream.str();
}
timepoint DatetimeUtils::get_now(){
    return std::chrono::system_clock::now();
}
std::string DatetimeUtils::get_formatted_now(enum timeformat tf){
    return format_datetime(DatetimeUtils::get_now(), tf);
}
