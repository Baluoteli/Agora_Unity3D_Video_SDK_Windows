#pragma once

#include "AgoraUilc.h"
using namespace AgoraSdkCWrapperUtilc;

class CAgoraOpenGl
{
public:
	static CAgoraOpenGl* getInstance();
	static void releaseInstance();

	~CAgoraOpenGl();

private:
	CAgoraOpenGl();

	struct CGraba{
		CGraba(){ ; }
		~CGraba(){
			if (nullptr != m_pAgoraOpenGL){
				delete m_pAgoraOpenGL;
				m_pAgoraOpenGL = nullptr;
			}
		}
	};

private:

	static CAgoraOpenGl* m_pAgoraOpenGL;
	static CLock m_Lock;

};