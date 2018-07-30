/*
 * ThreadBase.h
 *
 *  Created on: Mar 27, 2013
 *      Author: xxcc
 */

#ifndef THREADBASE_H_
#define THREADBASE_H_

#include <boost/thread.hpp>
#include <iostream>
using namespace std;

class ThreadBase
{
public:
	ThreadBase();
	virtual ~ThreadBase();

protected:
	boost::thread m_thread;

public:
	bool start();
	void stop();
	bool isRunning();

	virtual void operator()() = 0;

};

#endif /* THREADBASE_H_ */
