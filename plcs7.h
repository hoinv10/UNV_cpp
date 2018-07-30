#ifndef PLCS7_H
#define PLCS7_H
#include <iostream>
#include "snap7.h"
#include <string.h>
#include <boost/format.hpp>

using namespace std;


class PlcS7
{
public:
    union
    {
        uint32_t num;
        float fnum;
    } ConvertFI;

    PlcS7(string ip, int rack, int slot);
    ~PlcS7();
    void connect();
    TS7Client *plc;

    bool BitOf(byte input, int n);
    byte setbit(byte num, int pos, int val);
    word setbit(word num, int pos, int val);

    byte ReadQ_byte(string Q);
    bool ReadQ_bit(string QX);
    byte ReadI_byte(string I);
    bool ReadI_bit(string IX);
    void WriteQ_byte(string Q, byte val);
    void WriteQ_bit(string QX, int val);

    byte* ReadDB_Arrbyte(int DBArea,int DBD, int size);
    byte* ReadDB_Arrbyte(string DB, int size);
    byte ReadDB_byte(string DB);
    bool ReadDB_bit(string DBX);
    int16_t ReadDB_int16(string DBW);
    word ReadDB_word(string DBW);
    float ReadDB_float(string DBDW);


    void WriteDB_byte(string DB, byte val);
    void WriteDB_bit(string DBX, int val);
    void WriteDB_word(string DB, word val);
    void WriteDB_int16(string DB, int16_t val);
    void WriteDB_float(string DB, float val);

    bool Connected;
    void ShowBool(byte input);
private:
    string ip;
    int rack;
    int slot;
};

#endif // PLCS7_H
