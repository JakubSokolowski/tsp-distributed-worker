#include <iostream>
#include <ostream>
#include "worker/Worker.h"
int main() {
    auto conf = ConfigurationProvider();
    auto worker = Worker(conf);
    worker.Run();
    return 0;
}