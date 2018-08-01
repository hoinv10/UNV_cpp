#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <string>
#include <boost/array.hpp>
#include "ThreadBase.h"
#include <boost/signal.hpp>
#include <boost/bind.hpp>

using namespace  std;

class tcpclient :public ThreadBase
{
public:
    tcpclient(string host, int port);
    ~tcpclient();
    void connect();
    void close();
    void send_str(string msg);
    string receive_until();
    string receive_package();
    virtual void stop();
    virtual void run();
    void operator()();
    boost::signal<void (string)> HandlerSignal;
private:
    int port;
    string host;
    boost::asio::ip::tcp::socket *socket;
    boost::system::error_code error;
};

#endif // TCPSOCKET_H
