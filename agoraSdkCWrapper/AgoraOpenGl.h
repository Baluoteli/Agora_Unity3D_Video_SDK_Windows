#pragma once

#include "AgoraUilc.h"
using namespace AgoraSdkCWrapperUtilc;

#include "glew.h"
#include "glut.h"
#include "stdint.h"

class CAgoraOpenGl
{
public:
	static CAgoraOpenGl* getInstance();
	static void releaseInstance();

	~CAgoraOpenGl();

	void InitOpenGl(const int &nWidth, const int &nHeight);
	void updateVideo(UINT uid);
	void unInitOpenGl();

protected:

	static void RenderVideo();
	static void RenderTime(int value);

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
	
	static UINT m_uUidLocal;
	static uint8_t* m_pBufferOpenGl;
	static bool m_bIsInit;

	static int m_nWidth;
	static int m_nHeight;

	static const int screen_w = 500;
	static const int screen_h = 500;

	static AgoraSdkCWrapperUtilc::CFileIO m_fileRGBA;
};


class CAgoraOpenGLTexture{

public:
	static CAgoraOpenGLTexture* getInstance();
	static void releaseInstance();

	~CAgoraOpenGLTexture();

	int generateNativeTexture();
	int updateTexture(GLuint texId, unsigned int uid);
	void deleteTexture(GLuint texId);

protected:

	struct CGraba{
		CGraba(){ ; }
		~CGraba(){
			if (nullptr != m_pAgoraOpenGlTexture){
				delete m_pAgoraOpenGlTexture;
				m_pAgoraOpenGlTexture = nullptr;
			}
		}
	};

private:
	CAgoraOpenGLTexture();

	static CAgoraOpenGLTexture* m_pAgoraOpenGlTexture;
	static CLock m_lock;

	std::list<GLuint /*texture*/> mTextures;
	uint8_t* m_pBufferRenderTexture;
};

