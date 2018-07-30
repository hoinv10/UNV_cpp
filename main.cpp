#include <QCoreApplication>
#include "tcpsocket.h"
#include <unvhandledata.h>
#include "powerandcontrol.h"
#include "plcs7.h"
#include "plc_tuthu.h"
#include "unv_ipaddress.h"
#include "udpReceiver.h"
#include "plc_tuDKTC.h"
#include <boost/format.hpp>

void TestS7()
{
    PlcS7 *plc = new PlcS7(PLC_THU_IPADRESS,0,1);
    plc->connect();
//    cout <<"var1 = " << plc->ReadDB_bit(2,0,0) << endl;
//    cout <<"var2 = " << int(plc->ReadDB_byte(2,1)) << endl;
//    cout <<"var3 = " << plc->ReadDB_int16(2,2) << endl;
//    cout <<"var4 = " << plc->ReadDB_word(2,4) << endl;
   cout <<"var5 = "<< boost::format("%11.2f") % plc->ReadDB_float(2,6) << endl;
//    byte *data = plc->ReadDB_Arrbyte(2,6,4);
//    plc->ShowBool(data[0]);
//    plc->ShowBool(data[1]);
//    plc->ShowBool(data[2]);
//    plc->ShowBool(data[3]);
}
void TestTCP()
{
    tcpsocket *xlth = new tcpsocket(TCP_IPADRESS,TCP_PORT);
    UNVHandleData b;
    xlth->connect();
    xlth->HandlerSignal.connect(bind(&UNVHandleData::handler, &b,_1));
    xlth->send_str("test");
    usleep(1000);
    cout << "receive data:" << xlth->receive_until() << endl;
    xlth->start();
}

// udp
void TestUDP() // run UDP.py in folder
{
    UdpReceiver *client = new UdpReceiver();
    client->start();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TestS7();
    return a.exec();
}
