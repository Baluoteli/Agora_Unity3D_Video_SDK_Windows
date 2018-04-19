#include "AgoraOpenGl.h"

CAgoraOpenGl* CAgoraOpenGl::m_pAgoraOpenGL = nullptr;
CLock CAgoraOpenGl::m_Lock;

CAgoraOpenGl* CAgoraOpenGl::getInstance(){
	if (nullptr == m_pAgoraOpenGL){
		CAutoLock al(&m_Lock);
		if (nullptr == m_pAgoraOpenGL){
			m_pAgoraOpenGL = new CAgoraOpenGl;
		}
	}

	return m_pAgoraOpenGL;
}

void CAgoraOpenGl::releaseInstance(){

	if (nullptr != m_pAgoraOpenGL){
		delete m_pAgoraOpenGL; 
		m_pAgoraOpenGL = nullptr;
	}
}

CAgoraOpenGl::~CAgoraOpenGl(){

}

CAgoraOpenGl::CAgoraOpenGl(){

}

