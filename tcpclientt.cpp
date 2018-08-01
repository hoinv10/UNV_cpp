#include "tcpclient.h"

tcpclient::tcpclient(string host, int port)
{
    this->port = port;
    this->host = host;

}

void tcpclient::connect()
{
    boost::asio::io_service ios;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
    socket = new boost::asio::ip::tcp::socket(ios);
    socket->connect(endpoint);
}

void tcpclient::close()
{
    socket->close();
}



void tcpclient::send_str(string msg)
{
    boost::array<char, 128> buf;
    std::copy(msg.begin(),msg.end(),buf.begin());
    boost::system::error_code error;
    socket->write_some(boost::asio::buffer(buf, msg.size()), error);
#ifdef DEBUG
    if (error)
    {
        cout << "Send error: " << error.message() << endl;
    }
    else
    {
        cout << "Send data:" << msg << error.message() << endl;
    }
#endif
}

string tcpclient::receive_until()
{
    std::string ReadBuffer;
    std::stringstream message_stream;
    boost::asio::streambuf buffer;
    size_t len = read_until(*socket, buffer, '\n', error);
    if (len)
    {
      message_stream.write(boost::asio::buffer_cast<const char *>(buffer.data()), len);
      ReadBuffer = message_stream.str();
      // handle buffer...
      HandlerSignal(ReadBuffer);
    }
    return ReadBuffer;
}

string tcpclient::receive_package()
{
    string msg;
    return msg;
}

tcpclient::~tcpclient()
{
    if (socket != NULL)
    {
        socket->close();
        delete socket;
    }
}

void tcpclient::operator ()()
{
    run();
}

void tcpclient::stop()
{

}

void tcpclient::run()
{
    cout << "Start thread TCP socket" << endl;

    while (true)
    {
        receive_until();
    }
}
