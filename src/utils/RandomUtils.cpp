#include "../../include/utils/RandomUtils.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));

int RandomUtils::randomInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

double RandomUtils::randomDouble(double min, double max) {
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

std::string RandomUtils::randomString(int length, bool includeNumbers) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const std::string charsWithNumbers = chars + "0123456789";
    const std::string& source = includeNumbers ? charsWithNumbers : chars;
    
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; i++) {
        result += source[randomInt(0, static_cast<int>(source.length() - 1))];
    }
    return result;
}

std::string RandomUtils::randomEmail() {
    std::vector<std::string> domains = {"gmail.com", "yahoo.com", "hotmail.com", "restaurant.com"};
    std::string username = randomString(randomInt(5, 10), true);
    std::string domain = randomChoice(domains);
    return username + "@" + domain;
}

std::string RandomUtils::randomPhoneNumber() {
    std::ostringstream oss;
    oss << "+1";
    for (int i = 0; i < 10; i++) {
        oss << randomInt(0, 9);
    }
    return oss.str();
}

std::string RandomUtils::randomDate(const std::string& startDate, const std::string& endDate) {
    // Simple implementation - returns a date between start and end
    // For a full implementation, you'd parse the dates and generate a random date in between
    return startDate; // Placeholder
}

std::string RandomUtils::randomTime() {
    std::ostringstream oss;
    int hour = randomInt(0, 23);
    int minute = randomInt(0, 59);
    oss << std::setfill('0') << std::setw(2) << hour << ":"
        << std::setfill('0') << std::setw(2) << minute << ":00";
    return oss.str();
}

bool RandomUtils::randomBool() {
    return randomInt(0, 1) == 1;
}

void RandomUtils::seed(unsigned int seedValue) {
    generator.seed(seedValue);
}

