#ifndef TSP_WORKER_WORKER_H
#define TSP_WORKER_WORKER_H

#include "ConfigurationProvider.h"
#include <boost/asio.hpp>
class Worker {
public:
    Worker(const ConfigurationProvider &provider);
    void Run();
private:
    ConfigurationProvider configuration_provider;
    boost::asio::ip::tcp::endpoint getTCPEndpoint();
};


#endif //TSP_WORKER_WORKER_H
