#include "../../include/utils/TimeUtils.h"
#include <sstream>
#include <iomanip>
#include <ctime>

std::string TimeUtils::getCurrentDateTime() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string TimeUtils::getCurrentDate() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

std::string TimeUtils::getCurrentTime() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S");
    return oss.str();
}

std::time_t TimeUtils::stringToTime(const std::string& dateTime) {
    std::tm tm = {};
    std::istringstream ss(dateTime);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::mktime(&tm);
}

std::string TimeUtils::timeToString(std::time_t time) {
    auto tm = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

bool TimeUtils::isTimeBetween(const std::string& time, const std::string& start, const std::string& end) {
    // Simple implementation - can be enhanced
    return time >= start && time <= end;
}

int TimeUtils::getMinutesDifference(const std::string& time1, const std::string& time2) {
    std::time_t t1 = stringToTime(time1);
    std::time_t t2 = stringToTime(time2);
    return static_cast<int>(std::difftime(t2, t1) / 60);
}

