/*
 * ThreadBase.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: xxcc
 */

#include "ThreadBase.h"

ThreadBase::ThreadBase()
{


}

ThreadBase::~ThreadBase()
{

}

bool ThreadBase::start()
{
    m_thread = boost::thread(boost::ref(*this));
    return true;
}

void ThreadBase::stop()
{
	m_thread.interrupt();
	m_thread.join();
}

bool ThreadBase::isRunning()
{
//	boost::thread NotAThread;
//	return (m_thread.get_id() != NotAThread.get_id());

	return !m_thread.timed_join(boost::get_system_time());
}





