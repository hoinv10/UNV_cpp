#ifndef UNVHANDLEDATA_H
#define UNVHANDLEDATA_H
#include <QObject>
#include <QDebug>
#include <iostream>
#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include "powerandcontrol.h"

using namespace std;

class UNVHandleData
{
public:
    UNVHandleData();
    void handler(string buff);
};

#endif // UNVHANDLEDATA_H
