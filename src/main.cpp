#include <iostream>
#include <ostream>
#include "worker/Worker.h"
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using json = nlohmann::json;

int main(int argc, char** argv) {
    auto confProvider = ConfigurationProvider();
    if(argc > 1) {
        std::string path = argv[1];
        confProvider.ReadConfiguration(path);
    }
    auto conf = confProvider.GetConfiguration();
    std::cout << conf.retry_interval_ms << std::endl;
    std::cout << conf.port_num << std::endl;
    std::cout << conf.host << std::endl;

    for(;;) {
        try {
            auto worker = Worker(confProvider);
            worker.Run();
            if(worker.finished)
                break;
        } catch(const std::exception &ex) {
            std::cout << "Failed to construct socket, retrying in " << conf.retry_interval_ms << " ms" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(conf.retry_interval_ms));
        }
    }

    return 0;
}