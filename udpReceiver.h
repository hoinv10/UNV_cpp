#ifndef UDPCLIENT_H
#define UDPCLIENT_H
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "ThreadBase.h"
#include "unv_ipaddress.h"
using namespace std;
using boost::asio::ip::udp;
using boost::asio::ip::address;

struct Udp_Client {
    boost::asio::io_service io_service;
    udp::socket socket{io_service};
    boost::array<char, 1024> recv_buffer;
    udp::endpoint remote_endpoint;
    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred) {
        if (error) {
            std::cout << "Receive failed: " << error.message() << "\n";
            return;
        }
        std::cout << "Received: '" << std::string(recv_buffer.begin(), recv_buffer.begin()+bytes_transferred) << "' (" << error.message() << ")\n";
        wait();
    }
    void wait() {
        socket.async_receive_from(boost::asio::buffer(recv_buffer),
            remote_endpoint,
            boost::bind(&Udp_Client::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
    void Receiver()
    {
        socket.open(udp::v4());
        socket.bind(udp::endpoint(address::from_string(UDP_IPADDRESS), UDP_PORT));
        wait();
        std::cout << "Receiving\n";
        io_service.run();
        std::cout << "Receiver exit\n";
    }
};

class UdpReceiver:public ThreadBase
{
public:
    UdpReceiver();
    Udp_Client client;
    virtual void stop();
    virtual void run();
    void operator()();
private:

};
#endif // UDPCLIENT_H
