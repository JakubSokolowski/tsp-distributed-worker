#include <fstream>
#include "ConfigurationProvider.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

SocketConfiguration ConfigurationProvider::GetConfiguration() const {
    return configuration;
}

void ConfigurationProvider::ReadConfiguration(const std::string &path) {
    std::ifstream ifs(path);
    if(ifs.fail())
        return;
    json config = json::parse(ifs);
    configuration.host = config["host"];
    configuration.port_num = config["port"];
    configuration.retry_interval_ms = config["retryIntervalMs"];
}

