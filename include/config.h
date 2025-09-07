#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class Config {
private:
    nlohmann::json configData;
    std::vector<std::string> split(const std::string& str, char delimiter);

public:
    explicit Config(const std::string& filename);
    std::string getKey(const std::string& path);
};
