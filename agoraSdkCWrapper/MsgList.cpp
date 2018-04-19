#include "MsgList.h"

CFifoCmd* CFifoCmd::m_pFifoCmd = nullptr;
CFifoCmd::CGraba CFifoCmd::m_graba;

CFifoCmd* CFifoCmd::getInstance(){

	if (nullptr == m_pFifoCmd){
		m_pFifoCmd = new CFifoCmd;
	}

	return m_pFifoCmd;
}

void CFifoCmd::releaseInstance(){
	if (nullptr != m_pFifoCmd){

		delete m_pFifoCmd;
		m_pFifoCmd = nullptr;
	}
}

CFifoCmd::CFifoCmd(){
}

CFifoCmd::~CFifoCmd(){
	m_msgQueue.empty();
	m_pFifoCmd = nullptr;
}

void CFifoCmd::pushCmd(const std::string &msg){
	m_msgQueueMutex.lock();
	m_msgQueue.push(msg);

	if (m_msgQueue.size() > 100){
		m_msgQueue.pop();
	}

	m_msgQueueMutex.unlock();
}

std::string CFifoCmd::popCmd(){

	m_msgQueueMutex.lock();
	std::string msg;
	if (m_msgQueue.size() > 0){

		msg = m_msgQueue.front();
		m_msgQueue.pop();
	}
	m_msgQueueMutex.unlock();

	return msg;
}

int CFifoCmd::getCount()
{
	m_msgQueueMutex.lock();

	int nCount = m_msgQueue.size();
	m_msgQueueMutex.unlock();

	return nCount;
}