#ifndef TSP_WORKER_CONFIGURATIONPROVIDER_H
#define TSP_WORKER_CONFIGURATIONPROVIDER_H

#include <string>
struct SocketConfiguration {
    unsigned short port_num;
    std::string address;
};

class ConfigurationProvider {
public:
    SocketConfiguration GetConfiguration() const;
};


#endif //TSP_WORKER_CONFIGURATIONPROVIDER_H
