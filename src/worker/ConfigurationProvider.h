#ifndef TSP_WORKER_CONFIGURATIONPROVIDER_H
#define TSP_WORKER_CONFIGURATIONPROVIDER_H

#include <string>
struct SocketConfiguration {
    unsigned short port_num;
    std::string host;
    unsigned int retry_interval_ms;
};

class ConfigurationProvider {
private:
    SocketConfiguration configuration{42069, "127.0.0.1", 5000};
public:
    ConfigurationProvider()= default;
    SocketConfiguration GetConfiguration() const;
    void ReadConfiguration(const std::string & path);
};


#endif //TSP_WORKER_CONFIGURATIONPROVIDER_H
