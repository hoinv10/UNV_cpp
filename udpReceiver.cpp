#include "udpReceiver.h"

UdpReceiver::UdpReceiver()
{

}

void UdpReceiver::operator ()()
{
    run();
}

void UdpReceiver::stop()
{

}

void UdpReceiver::run()
{
    cout << "Start thread Udp socket" << endl;
    client.Receiver();
    //handler event here
//    while (true)
//    {

//    }
}
