#ifndef PLC_TUDKTC_H
#define PLC_TUDKTC_H
#include "plcs7.h"

#define    ControlMode_Auto                 = 0
#define    ControlMode_Manual               = 1
#define    ControlMode_Stop                 = 2

#define    HydraulicMode_running            = 0
#define    HydraulicMode_rtrienkhaixong     = 1
#define    HydraulicMode_rthuhoixong        = 2

class Plc_TuDKTC:public PlcS7
{
public:
    Plc_TuDKTC(string ip, int rack, int slot);
    byte RCMode;
    byte PCMode;
    byte HCStatus;

    bool FireAlarm, AC_IN_EleclGen, AC_IN_ElecNet,AC_IN_UPS,
         DC_IN_UPS, DC_IN_ACDC,     SPD_01, SPD_02,SPD_03,
         Power_Hydraulic_Cabine,    Power_Receive_Cabinet,    Power_Infomation_Machine;
    void ReadStatus();
};

#endif // PLC_TUTHU_H
