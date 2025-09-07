#include "config.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using json = nlohmann::json;

Config::Config(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open config file: " + filename);
    }
    file >> configData;
}

std::vector<std::string> Config::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string Config::getKey(const std::string& path) {
    std::vector<std::string> keys = split(path, '.');
    json current = configData;

    for (const auto& key : keys) {
        if (!current.contains(key)) {
            throw std::runtime_error("Key not found: " + key);
        }
        current = current[key];
    }

    if (current.is_string()) return current.get<std::string>();
    if (current.is_number_integer()) return std::to_string(current.get<int>());
    if (current.is_number_float()) return std::to_string(current.get<double>());
    if (current.is_boolean()) return current.get<bool>() ? "true" : "false";

    return current.dump(); // fallback for arrays/objects
}
