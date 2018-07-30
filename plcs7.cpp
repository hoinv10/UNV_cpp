#include "plcs7.h"

PlcS7::PlcS7(string ip, int rack, int slot)
{
    this->ip = ip;
    this->rack = rack;
    this->slot = slot;
    Connected = false;
}

// Open connection to PLC------------------------------------
void PlcS7::connect()
{
    plc = new TS7Client();
    char *IpAdd = new char[ip.length() + 1];
    strcpy(IpAdd, ip.c_str());
    plc->ConnectTo(IpAdd,rack,slot);
    if (plc->Connected())
    {
        Connected = true;
        cout << "\033[0;32m" << "Connected to PLC: " << ip << " Rack: " << rack << " Slot: " << slot << "\033[0m" <<endl;
    }
    else
    {
        cout<< "\033[0;31m" << "Connect fail to device" << "\033[0m" << endl;
    }
}
// read Ouput register-----------------------------------------
byte PlcS7::ReadQ_byte(int OutputArea) // Q0 => ReadQ_byte(0)
{
    if (Connected)
    {
        byte Output[1];
        plc->ABRead(OutputArea,1,&Output);
        return Output[0];
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}

bool PlcS7::ReadQ_bit(int OutputArea, int bit) // Q0.0 => ReadQ_bit(0,0)
{
    if (Connected)
    {
        byte Output[1];
        plc->ABRead(OutputArea,1,&Output);
        return BitOf(Output[0],bit);
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}
// read Input register---------------------------------------
byte PlcS7::ReadI_byte(int InputArea) // I0 => ReadI_byte(0)
{
    if (Connected)
    {
        byte Input[1];
        plc->EBRead(InputArea,1,&Input);
        return Input[0];
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}
bool PlcS7::ReadI_bit(int InputArea,int bit) // I0.0 => ReadI_bit(0,0)
{
    if (Connected)
    {
        byte Input[1];
        plc->EBRead(InputArea,1,&Input);
        return BitOf(Input[0],bit);
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}
// write to Output Resistor ---------------------------------
void PlcS7::WriteQ_byte(int OutputArea, byte val)
{
    if (Connected)
    {
        plc->ABWrite(OutputArea,1,&val);
    }
    else
    {
        cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
}
void PlcS7::WriteQ_bit(int OutputArea, int bit, int val)
{
    if (Connected)
    {
        byte Q = ReadQ_byte(OutputArea);
        Q = setbit(Q,bit,val);
        WriteQ_byte(OutputArea,Q);
        Q = ReadQ_byte(OutputArea);
        cout << "\033[0;32m" << "Writed Q"<<OutputArea<<"."<<bit<<"="<<val << "\033[0m" <<endl;
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
}

// Read data from data block-------------------------------
byte* PlcS7::ReadDB_Arrbyte(int DBArea,int DBD, int size)
{
    if (Connected)
    {
        byte *db;
        db = (byte *)malloc(sizeof(byte)*size);
        plc->DBRead(DBArea,DBD,size,db);
        return db;
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}

byte PlcS7::ReadDB_byte(int DBArea, int DBD)
{
    if (Connected)
    {
        byte db;
        plc->DBRead(DBArea,DBD,1,&db);
        return db;
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}

bool PlcS7::ReadDB_bit(int DBArea,int DBD, int bit)
{
    if (Connected)
    {
        byte db;
        plc->DBRead(DBArea,DBD,1,&db);
        return BitOf(db,bit);
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}
int16_t PlcS7::ReadDB_int16(int DBArea, int DBD)
//db0.dbd4 => ReadDB_word(0,4)
{
    if (Connected)
    {
        byte *db;
        db = ReadDB_Arrbyte(DBArea,DBD,2);
        int16_t out = int16_t(db[0] << 8 | db[1]);
        free (db);
        return out;
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}

word PlcS7::ReadDB_word(int DBArea, int DBD)
//db0.dbd4 => ReadDB_word(0,4)
{
    if (Connected)
    {
        byte *db;
        db = ReadDB_Arrbyte(DBArea,DBD,2);
        word out = word(db[0] << 8 | db[1]);
        free (db);
        return out;
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}
//float PlcS7::floatFromBits( uint32_t const bits )
//{
//    char    buffer[nBytes];
//    float   result;

//    memcpy( buffer, &bits, nBytes );
//    memcpy( &result, buffer, nBytes );
//    return result;
//}

float PlcS7::ReadDB_float(int DBArea, int DBD)
{
    if (Connected)
    {
//        byte *db;
//        db = ReadDB_Arrbyte(DBArea,DBD,4);
//        int32_t out = int32_t(db[0] << 24 | db[1] << 16 | db[2] << 8 | db[3]);
//        free (db);
        float out;
        plc->ReadArea(0x84,2,6,2,0x08,&out);
        return out;
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}

// Show byte data as bool format---------------------------
void PlcS7::ShowBool(byte input)
{
    string s = "";
    cout << "bool = " ;
    for (int i=0;i<8;i++){
        int temp = (input>>i&0x01);
        s = std::to_string(temp)+s;
    }
    cout << s << "b" << endl;
}

// Bit of byte --------------------------------------------
bool PlcS7::BitOf(byte input, int n)
{
    return (input>>n&0x01);
}

// set bit ------------------------------------------------
byte PlcS7::setbit(byte &num, int pos, int val)
{
    num = (val==0) ? num & (~(0x01 << pos)) : num|(0x01 << pos);
    return num;
}
word PlcS7::setbit(word &num, int pos, int val)
{
    num = (val==0) ? num & (~(0x0001 << pos)) : num|(0x0001 << pos);
    return num;
}
// Destructor ---------------------------------------------
PlcS7::~PlcS7()
{
    if (plc != NULL)
    {
        delete plc;
    }
}
