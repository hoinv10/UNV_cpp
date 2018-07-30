#include "plc_tuDKTC.h"


Plc_TuDKTC::Plc_TuDKTC(string ip, int rack, int slot):PlcS7(ip, rack,slot)
{

}

void Plc_TuDKTC::ReadStatus()
{
     byte *db2  = ReadDB_Arrbyte(2,0,4);
     RCMode     = db2[0];
     PCMode     = db2[1];
     HCStatus   = db2[2];
     FireAlarm                  = BitOf(db2[3],0);
     AC_IN_EleclGen             = BitOf(db2[3],1);
     AC_IN_ElecNet              = BitOf(db2[3],2);
     AC_IN_UPS                  = BitOf(db2[3],3);
     DC_IN_UPS                  = BitOf(db2[3],4);
     DC_IN_ACDC                 = BitOf(db2[3],5);
     SPD_01                     = BitOf(db2[3],6);
     SPD_02                     = BitOf(db2[3],7);
     SPD_03                     = BitOf(db2[4],0);
     Power_Hydraulic_Cabine     = BitOf(db2[4],1);
     Power_Receive_Cabinet      = BitOf(db2[4],2);
     Power_Infomation_Machine   = BitOf(db2[4],3);
     free(db2);
}

