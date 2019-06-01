#include <iostream>
#include <ostream>
#include "worker/Worker.h"
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using json = nlohmann::json;

int main() {
    auto conf = ConfigurationProvider();
    for(;;) {
        try {
            auto worker = Worker(conf);
            worker.Run();
            if(worker.finished)
                break;
        } catch(std::exception ex) {
            std::cout << "Failed to construct socket, retrying in 5s" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }
    }

    return 0;
}