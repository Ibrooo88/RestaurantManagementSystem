#ifndef RANDOMUTILS_H
#define RANDOMUTILS_H

#include <string>
#include <vector>

class RandomUtils {
public:
    static int randomInt(int min, int max);
    static double randomDouble(double min, double max);
    static std::string randomString(int length, bool includeNumbers = true);
    static std::string randomEmail();
    static std::string randomPhoneNumber();
    static std::string randomDate(const std::string& startDate, const std::string& endDate);
    static std::string randomTime();
    static bool randomBool();
    template<typename T>
    static T randomChoice(const std::vector<T>& choices);
    static void seed(unsigned int seed);
};

template<typename T>
T RandomUtils::randomChoice(const std::vector<T>& choices) {
    if (choices.empty()) {
        return T();
    }
    int index = randomInt(0, static_cast<int>(choices.size() - 1));
    return choices[index];
}

#endif // RANDOMUTILS_H

