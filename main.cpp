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

const string var1 = "DB2.DBDX0.0";
const string var2 = "DB2.DBD1";
const string var3 = "DB2.DBW2";
const string var4 = "DB2.DBW4";
const string var5 = "DB2.DBDW6";

void TestS7()
{
    PlcS7 *plc = new PlcS7(PLC_THU_IPADRESS,0,1);
    plc->connect();
    float x = 12.34;
    plc->WriteDB_float(var5,x);
    cout <<"var1 = " << plc->ReadDB_bit(var1) << endl;
    cout <<"var2 = " << int(plc->ReadDB_byte(var2)) << endl;
    cout <<"var3 = " << plc->ReadDB_int16(var3) << endl;
    cout <<"var4 = " << plc->ReadDB_word(var4) << endl;
    cout <<"var5 = "<<  plc->ReadDB_float(var5)<< endl;
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
