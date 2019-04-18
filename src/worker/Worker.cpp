#include "Worker.h"

#include <iostream>
using namespace boost::asio;
using ip::tcp;

using std::string;
using std::cout;
using std::endl;

Worker::Worker(const ConfigurationProvider &provider)
        : configuration_provider(provider)
{ }

void Worker::Run() {
    boost::asio::io_service io_service;
    tcp::socket socket(io_service);
    socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 42069 ));
    for(int i = 0; i < 5; i++) {
        const string msg = "Hello from Client!\n";
        boost::system::error_code error;
        boost::asio::write( socket, boost::asio::buffer(msg), error );
        if( !error ) {
            cout << "Client sent hello message!" << endl;
        }
        else {
            cout << "send failed: " << error.message() << endl;
        }
        boost::asio::streambuf receive_buffer;
        boost::asio::read_until(socket, receive_buffer, "\n");
        if( error && error != boost::asio::error::eof ) {
            cout << "receive failed: " << error.message() << endl;
        }
        else {
            const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
            cout << "Data" << data << endl;
        }
    }

    socket.close();
}

boost::asio::ip::tcp::endpoint Worker::getTCPEndpoint() {
    auto configuration = configuration_provider.GetConfiguration();
    auto address = boost::asio::ip::address::from_string(configuration.address);
    auto port = configuration.port_num;
    return boost::asio::ip::tcp::endpoint(address, port);
}
