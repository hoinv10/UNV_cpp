#ifndef PLCS7_H
#define PLCS7_H
#include <iostream>
#include "snap7.h"
#include <string.h>

using namespace std;

class PlcS7
{
public:

    PlcS7(string ip, int rack, int slot);
    ~PlcS7();
    void connect();
    TS7Client *plc;

    bool BitOf(byte input, int n);
    byte setbit(byte &num, int pos, int val);
    word setbit(word &num, int pos, int val);

    byte ReadI_byte(int InputArea);
    bool ReadI_bit(int InputArea,int bit);

    byte ReadQ_byte(int OutputArea);
    bool ReadQ_bit(int OutputArea, int bit);
    void WriteQ_byte(int OutputArea, byte val);
    void WriteQ_bit(int OutputArea, int bit, int val);

    byte* ReadDB_Arrbyte(int DBArea,int DBD, int size);
    byte ReadDB_byte(int DBArea, int DBD);
    bool ReadDB_bit(int DBArea,int DBD, int bit);
    int16_t ReadDB_int16(int DBArea, int DBD);
    word ReadDB_word(int DBArea, int DBD);
    float ReadDB_float(int DBArea, int DBD);
    void ShowBool(byte input);
    float floatFromBits( uint32_t const bits );
    bool Connected;
private:
    string ip;
    int rack;
    int slot;
};

#endif // PLCS7_H
