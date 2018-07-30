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
byte PlcS7::ReadQ_byte(string Q) // Q0 => ReadQ_byte(0)
{
    int OutputArea;
    sscanf(Q.c_str(), "Q%d",&OutputArea);
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

bool PlcS7::ReadQ_bit(string QX) // Q0.0 => ReadQ_bit(0,0)
{
    int OutputArea, bit;
    sscanf(QX.c_str(), "Q%d.%d",&OutputArea,&bit);
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
byte PlcS7::ReadI_byte(string I) // I0 => ReadI_byte("I0");
{
    int InputArea;
    sscanf(I.c_str(), "I%d",&InputArea);
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
bool PlcS7::ReadI_bit(string IX) // I0.0 => ReadI_bit(0,0)
{
    int InputArea,bit;
    sscanf(IX.c_str(), "I%d.%d",&InputArea, &bit);
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
void PlcS7::WriteQ_byte(string Q,  byte val)
{
    int OutputArea;
    sscanf(Q.c_str(), "Q%d",&OutputArea);
    if (Connected)
    {
        plc->ABWrite(OutputArea,1,&val);
    }
    else
    {
        cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
}
void PlcS7::WriteQ_bit(string QX, int val)
{
    int OutputArea,bit;
    sscanf(QX.c_str(), "Q%d.%d",&OutputArea,&bit);
    string DB = "Q" + std::to_string(OutputArea) ;
    if (Connected)
    {
        byte Q = ReadQ_byte(DB);
        Q = setbit(Q,bit,val);
        WriteQ_byte(DB,Q);
        Q = ReadQ_byte(DB);
        cout << "\033[0;32m" << "Writed Q"<<OutputArea<<"."<<bit<<"="<<val << "\033[0m" <<endl;
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
}

// Read data from data block-------------------------------
byte* PlcS7::ReadDB_Arrbyte(string DB, int size)
{
    int DBArea,DBD;
    sscanf(DB.c_str(), "DB%d.DBD%d",&DBArea,&DBD);
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
byte* PlcS7::ReadDB_Arrbyte(int DBArea, int DBD, int size)
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

byte PlcS7::ReadDB_byte(string DB)
{
    int DBArea,DBD;
    sscanf(DB.c_str(), "DB%d.DBD%d",&DBArea,&DBD);
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

bool PlcS7::ReadDB_bit(string DBX)
{
    int DBArea,DBD,bit;
    sscanf(DBX.c_str(), "DB%d.DBDX%d.%d",&DBArea,&DBD,&bit);
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
int16_t PlcS7::ReadDB_int16(string DBW)
{
    int DBArea,DBD;
    sscanf(DBW.c_str(), "DB%d.DBW%d",&DBArea,&DBD);
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

word PlcS7::ReadDB_word(string DBW)
{
    int DBArea,DBD;
    sscanf(DBW.c_str(), "DB%d.DBW%d",&DBArea,&DBD);
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

float PlcS7::ReadDB_float(string DBDW)
{
    int DBArea,DBD;
    sscanf(DBDW.c_str(), "DB%d.DBDW%d",&DBArea,&DBD);
    if (Connected)
    {
        byte *db;
        db = ReadDB_Arrbyte(DBArea,DBD,4);
        ConvertFI.num = uint32_t(db[0] << 24 | db[1] << 16 | db[2] << 8 | db[3]);
        free (db);
        return float(ConvertFI.fnum);
    }
    else
    {
        cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
    return 0;
}
// Write data to data block--------------------------------

void PlcS7::WriteDB_byte(string DB, byte val)
{
    int DBArea,DBD;
    sscanf(DB.c_str(), "DB%d.DBD%d",&DBArea,&DBD);
    if (Connected)
    {
        plc->DBWrite(DBArea,DBD,1, &val);
    }
    else
    {
        cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
}

void PlcS7::WriteDB_bit(string DBX, int val)
{
    int DBArea,DBD,bit;
    sscanf(DBX.c_str(), "DB%d.DBDX%d.%d",&DBArea,&DBD,&bit);
    string DB = "DB"+ std::to_string(DBArea) + ".DBD" + std::to_string(DBD);
    if (Connected)
    {
        byte read;
        read = ReadDB_byte(DB);
        read = setbit(read,bit,val);
        plc->DBWrite(DBArea,DBD,1, &read);
    }
    else
    {
          cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
}
void PlcS7::WriteDB_word(string DB, word val)
{
    int DBArea,DBD;
    sscanf(DB.c_str(), "DB%d.DBW%d",&DBArea,&DBD);
    if (Connected)
    {
        byte data[2];
        data[0] = (val >> 8) & 0x00ff;
        data[1] = val & 0x00ff;
        plc->DBWrite(DBArea,DBD,2, &data);
    }
    else
    {
        cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
}
void PlcS7::WriteDB_int16(string DB, int16_t val)
{
    int DBArea,DBD;
    sscanf(DB.c_str(), "DB%d.DBW%d",&DBArea,&DBD);
    if (Connected)
    {
        byte data[2];
        data[0] = (val >> 8) & 0x00ff;
        data[1] = val & 0x00ff;
        plc->DBWrite(DBArea,DBD,2,&data);
    }
    else
    {
        cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
}
void PlcS7::WriteDB_float(string DB, float val)
{
    int DBArea,DBD;
    sscanf(DB.c_str(), "DB%d.DBDW%d",&DBArea,&DBD);
    if (Connected)
    {
        ConvertFI.fnum = val;
        uint32_t ival = ConvertFI.num;
        byte data[4];
        data[0] = (ival >> 24) & 0x000000ff;
        data[1] = (ival >> 16) & 0x000000ff;
        data[2] = (ival >> 8) & 0x000000ff;
        data[3] =  ival & 0x000000ff;
        plc->DBWrite(DBArea,DBD,4, &data);
    }
    else
    {
        cout<< "\033[0;31m" << "Device disconnected to network" << "\033[0m" << endl;
    }
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
byte PlcS7::setbit(byte num, int pos, int val)
{
    num = (val==0) ? num & (~(0x01 << pos)) : num|(0x01 << pos);
    return num;
}
word PlcS7::setbit(word num, int pos, int val)
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
