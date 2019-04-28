#include "Worker.h"

#include <iostream>
using namespace boost::asio;
using ip::tcp;

using std::string;
using std::cout;
using std::endl;

Worker::Worker(const ConfigurationProvider &provider)
        : config_provider_m(provider)
        , socket_m(io_service_m)
{
    Connect();
}

Worker::Worker(const Worker & other)
        : config_provider_m(other.config_provider_m)
        , socket_m(io_service_m)
{
    Connect();
}

Worker::~Worker() {
    if(socket_m.is_open())
        socket_m.close();
}

void Worker::Run() {
    for(int i = 0; i < 20; i++) {
        Write("Hello from client");
        auto response = Read();
        cout << "Client received: " << response << endl;
    }

    socket_m.close();
}

void Worker::Write(const std::string &message) {
    boost::asio::write( socket_m, boost::asio::buffer(message + "\n"), error_m);
    HandleCommunicationError(error_m);
}

std::string Worker::Read() {
    const std::string end_of_message = "\n";
    boost::asio::streambuf receive_buffer;
    boost::asio::read_until(socket_m, receive_buffer, end_of_message);
    if( error_m && error_m != boost::asio::error::eof ) {
        cout << "Receive failed due to: " << error_m.message() << endl;
    } else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        cout << data << endl;
        return data;
    }
    return "";
}

void Worker::Connect() {
    auto endpoint = GetTCPEndpoint();
    socket_m.connect(endpoint);
}

boost::asio::ip::tcp::endpoint Worker::GetTCPEndpoint() const {
    auto configuration = config_provider_m.GetConfiguration();
    auto address = boost::asio::ip::address::from_string(configuration.address);
    auto port = configuration.port_num;
    return boost::asio::ip::tcp::endpoint(address, port);
}

void Worker::HandleCommunicationError(const boost::system::error_code &error) const {
    if( !error ) {
        cout << "Client sent message successfully." << endl;
    } else {
        cout << "Send failed. Reason: " << error.message() << endl;
    }
}
