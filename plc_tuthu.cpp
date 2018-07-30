#include "plc_tuthu.h"


Plc_TuThu::Plc_TuThu(string ip, int rack, int slot):PlcS7(ip, rack,slot)
{

}

void Plc_TuThu::ReadStatus()
{
     byte *db2 = ReadDB_Arrbyte(2,0,4);
     ControlMode    = db2[0];
     HydraulicMode  = db2[1];
     FireAlarm                  = BitOf(db2[2],0);
     AC_IN_EleclGen             = BitOf(db2[2],1);
     AC_IN_ElecNet              = BitOf(db2[2],2);
     AC_IN_UPS                  = BitOf(db2[2],3);
     DC_IN_UPS                  = BitOf(db2[2],4);
     DC_IN_ACDC                 = BitOf(db2[2],5);
     SPD_01                     = BitOf(db2[2],6);
     SPD_02                     = BitOf(db2[2],7);
     SPD_03                     = BitOf(db2[3],0);
     Power_Hydraulic_Cabine     = BitOf(db2[3],1);
     Power_Receive_Cabinet      = BitOf(db2[3],2);
     Power_Infomation_Machine   = BitOf(db2[3],3);

     free(db2);
}

