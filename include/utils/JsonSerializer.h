#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <string>
#include <vector>
#include <map>

class JsonSerializer {
public:
    // Serialize basic types
    static std::string serializeString(const std::string& value);
    static std::string serializeInt(int value);
    static std::string serializeDouble(double value);
    static std::string serializeBool(bool value);
    static std::string serializeNull();
    
    // Serialize objects
    static std::string serializeObject(const std::map<std::string, std::string>& fields);
    static std::string serializeArray(const std::vector<std::string>& items);
    
    // Helper methods
    static std::string escapeString(const std::string& str);
    static std::string formatNumber(double value, int precision = 2);
    
    // Deserialize (basic implementation)
    static std::map<std::string, std::string> deserializeObject(const std::string& json);
    static std::vector<std::string> deserializeArray(const std::string& json);
};

#endif // JSONSERIALIZER_H

