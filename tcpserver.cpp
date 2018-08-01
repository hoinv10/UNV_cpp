#include "tcpserver.h"

tcpServer::tcpServer(int port)
{
    this->port = port;
}


tcpServer::~tcpServer()
{
    if (_server != NULL)
        delete _server;
}

void tcpServer::operator ()()
{
    run();
}

void tcpServer::stop()
{

}

void tcpServer::run()
{
    cout << "Start thread server" << endl;
    _server = new server(io_service,port);
    io_service.run();
}
