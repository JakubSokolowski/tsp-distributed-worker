#ifndef TSP_WORKER_WORKER_H
#define TSP_WORKER_WORKER_H

#include "ConfigurationProvider.h"
#include <boost/asio.hpp>
class Worker {
public:
    Worker(const ConfigurationProvider &provider);
    Worker(const Worker&);
    ~Worker();
    void Run();

protected:
    void Write(const std::string& message);
    void HandleCommunicationError(const boost::system::error_code &error) const ;
    std::string Read();
private:
    ConfigurationProvider config_provider_m;
    boost::system::error_code error_m;
    boost::asio::io_service io_service_m {};
    boost::asio::ip::tcp::socket socket_m;
    boost::asio::ip::tcp::endpoint GetTCPEndpoint() const;

    void Connect();
};


#endif //TSP_WORKER_WORKER_H
