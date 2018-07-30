#include "unvhandledata.h"

UNVHandleData::UNVHandleData()
{

}
void UNVHandleData::handler(string buff)
{
    int ind;
    char type,length;
    char data[length];
    bool istruedata = false;

    char *cstr = new char[buff.length() + 1];
    strcpy(cstr, buff.c_str());

    for (ind=0; ind < strlen(cstr); ind++)
    {
        if (int(cstr[ind]) == CONTROLTYPE)
        {
            type = cstr[ind+1];
            length = cstr[ind+2];
            istruedata = true;
            break;            
        }
    }
#ifdef DEBUG
    cout << "Handler" << buff << endl;
    cout << "ControlType:" << int(cstr[ind]) << " Type:" << int(type) << " Length:" << int(length) << endl;
#endif

    if (istruedata)
    {
        switch (int(type))
        {
            case BETA_JOG:
                cout << "BETA_JOG" << endl;
                break;
            case EPSILON_JOG:
                cout << "EPSILON_JOG" << endl;
                break;
            case BETA_RP:
                cout << "BETA_RP" << endl;
                break;
            case EPSILON_RP:
                cout << "EPSILON_RP" << endl;
                break;
            case BETA_AP:
                cout << "BETA_AP" << endl;
                break;
            case EPSILON_AP:
                cout << "EPSILON_AP" << endl;
                break;
            case BETA_EPSILON_AP:
                cout << "BETA_EPSILON_AP" << endl;
                break;
            case THETA1_APS:
                cout << "THETA1_APS" << endl;
                break;
            case THETA2_APS:
                cout << "THETA2_APS" << endl;
                break;
            case BETA_SP:
                cout << "BETA_SP" << endl;
                break;
            case EPSILON_SP:
                cout << "EPSILON_SP" << endl;
                break;
            case QUET:
                cout << "QUET" << endl;
                break;
            case SUCSAO_VONG:
                cout << "SUCSAO_VONG" << endl;
                break;
            case SUCSAO_QUATLON:
                cout << "SUCSAO_QUATLON" << endl;
                break;
            case SUCSAO_QUATNHO:
                cout << "SUCSAO_QUATNHO" << endl;
                break;
            case SUCSAO_TUYCHINH:
                cout << "SUCSAO_TUYCHINH" << endl;
                break;
            case ENC_VAL:
                cout << "ENC_VAL" << endl;
                break;
            default:
                cout << "Error data";
        };
    }
}
