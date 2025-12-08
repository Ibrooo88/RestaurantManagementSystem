#include "../../include/utils/JsonSerializer.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

std::string JsonSerializer::serializeString(const std::string& value) {
    return "\"" + escapeString(value) + "\"";
}

std::string JsonSerializer::serializeInt(int value) {
    return std::to_string(value);
}

std::string JsonSerializer::serializeDouble(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}

std::string JsonSerializer::serializeBool(bool value) {
    return value ? "true" : "false";
}

std::string JsonSerializer::serializeNull() {
    return "null";
}

std::string JsonSerializer::serializeObject(const std::map<std::string, std::string>& fields) {
    std::ostringstream oss;
    oss << "{";
    bool first = true;
    for (const auto& [key, value] : fields) {
        if (!first) oss << ",";
        oss << "\"" << escapeString(key) << "\":" << value;
        first = false;
    }
    oss << "}";
    return oss.str();
}

std::string JsonSerializer::serializeArray(const std::vector<std::string>& items) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < items.size(); i++) {
        if (i > 0) oss << ",";
        oss << items[i];
    }
    oss << "]";
    return oss.str();
}

std::string JsonSerializer::escapeString(const std::string& str) {
    std::string escaped;
    escaped.reserve(str.length());
    
    for (char c : str) {
        switch (c) {
            case '"': escaped += "\\\""; break;
            case '\\': escaped += "\\\\"; break;
            case '\b': escaped += "\\b"; break;
            case '\f': escaped += "\\f"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default:
                if (static_cast<unsigned char>(c) < 0x20) {
                    std::ostringstream oss;
                    oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') 
                        << static_cast<int>(c);
                    escaped += oss.str();
                } else {
                    escaped += c;
                }
                break;
        }
    }
    
    return escaped;
}

std::string JsonSerializer::formatNumber(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

std::map<std::string, std::string> JsonSerializer::deserializeObject(const std::string& json) {
    std::map<std::string, std::string> result;
    // Basic implementation - for full JSON parsing, consider using a library
    // This is a simplified version
    return result;
}

std::vector<std::string> JsonSerializer::deserializeArray(const std::string& json) {
    std::vector<std::string> result;
    // Basic implementation - for full JSON parsing, consider using a library
    // This is a simplified version
    return result;
}

