#ifndef DATETIMEUTILS_H
#define DATETIMEUTILS_H

#include <string>
#include <chrono>

enum timeformat{ FILENAME, STANDART };

typedef std::chrono::system_clock::time_point timepoint;

class DatetimeUtils {
public:
    static timepoint get_now();
    static std::string get_formatted_now(enum timeformat tf);
    static std::string format_datetime(timepoint p, enum timeformat tf);
};

#endif // DATETIMEUTILS_H
