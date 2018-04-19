#ifndef __MSGLIST_H__
#define __MSGLIST_H__

#include <mutex>
#include <queue>
#pragma warning(disable:4172)

class CFifoCmd{

public:
	static CFifoCmd* getInstance();
	static void releaseInstance();
	~CFifoCmd();

	void pushCmd(const std::string &msg);
	std::string popCmd();
	int getCount();

private:
	CFifoCmd();

protected:

	struct CGraba{
	public:
		CGraba(){ ; }
		~CGraba(){
			if (nullptr != m_pFifoCmd){
				delete m_pFifoCmd;
				m_pFifoCmd = nullptr;
			}
		}
	};
	
	static CGraba m_graba;
private:

	std::queue<std::string> m_msgQueue;
	std::mutex m_msgQueueMutex;

	static CFifoCmd* m_pFifoCmd;
};

#endif