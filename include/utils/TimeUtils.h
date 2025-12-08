#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <ctime>

class TimeUtils {
public:
    static std::string getCurrentDateTime();
    static std::string getCurrentDate();
    static std::string getCurrentTime();
    static std::time_t stringToTime(const std::string& dateTime);
    static std::string timeToString(std::time_t time);
    static bool isTimeBetween(const std::string& time, const std::string& start, const std::string& end);
    static int getMinutesDifference(const std::string& time1, const std::string& time2);
};

#endif // TIMEUTILS_H

