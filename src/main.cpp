#include <iostream>
#include <ostream>
#include "worker/Worker.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    auto conf = ConfigurationProvider();
    auto worker = Worker(conf);
    worker.Run();
    return 0;
}