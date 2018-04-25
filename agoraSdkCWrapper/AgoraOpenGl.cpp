#include "AgoraOpenGl.h"
#include "CBufferMgr.h"

CAgoraOpenGl* CAgoraOpenGl::m_pAgoraOpenGL = nullptr;
CLock CAgoraOpenGl::m_Lock;
bool CAgoraOpenGl::m_bIsInit = FALSE;

int CAgoraOpenGl::m_nWidth = 0;
int CAgoraOpenGl::m_nHeight = 0;

UINT CAgoraOpenGl::m_uUidLocal = 0;
uint8_t* CAgoraOpenGl::m_pBufferOpenGl = nullptr;

AgoraSdkCWrapperUtilc::CFileIO CAgoraOpenGl::m_fileRGBA;

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

void CAgoraOpenGl::RenderVideo(){

#if 0
	//Make picture full of window
	//Move to(-1.0,1.0)
	glRasterPos3f(-1.0f, 1.0f, 0);
	//Zoom, Flip
	glPixelZoom((float)screen_w / (float)m_nWidth, -(float)screen_h / m_nHeight);
	
	int nBufferLenOut = 0;
	int nWidth = 0;
	int nHeight = 0;
	if (CBufferMgr::getInstance()->popYUVBuffer(m_uUidLocal, m_pBufferOpenGl, nBufferLenOut, nWidth, nHeight)){

		assert(m_nWidth == nWidth && m_nHeight == nHeight);
	//	m_fileRGBA.write((char*)m_pBufferOpenGl, nBufferLenOut);

		glDrawPixels(m_nWidth, m_nHeight, GL_BGRA, GL_UNSIGNED_BYTE, m_pBufferOpenGl);
		glutSwapBuffers();
	}

#endif
}

void CAgoraOpenGl::RenderTime(int value){

#if 0
	RenderVideo();
	if (m_bIsInit)
		glutTimerFunc(66, RenderTime, 0);

#endif
}

CAgoraOpenGl::CAgoraOpenGl(){

	std::string strPathRGBA = CAgoraWrapperUtilc::getAbsoluteDir() + "openGl_argb.yuv";
	m_fileRGBA.openMedia(strPathRGBA.data());
}

CAgoraOpenGl::~CAgoraOpenGl(){

	m_fileRGBA.close();
}

void CAgoraOpenGl::InitOpenGl(const int &nWidth,const int &nHeight){
	
#if 0
	m_bIsInit = TRUE;
	assert(nWidth && nHeight);
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	
	if (nullptr == m_pBufferOpenGl){
		m_pBufferOpenGl = new uint8_t[m_nWidth * m_nHeight * 4];
		ZeroMemory(m_pBufferOpenGl, m_nWidth * m_nHeight * 4);
	}

	int nArgc = 1;
	char *cArgv[] = { "OpenGL init"};
	glutInit(&nArgc, cArgv);
	//Double, Use glutSwapBuffers() to show
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Agora OpenGl");
#endif
}

void CAgoraOpenGl::unInitOpenGl()
{
	m_bIsInit = FALSE;
}

void CAgoraOpenGl::updateVideo(UINT uid){

	m_uUidLocal = uid;

#if 0
	glutDisplayFunc(&RenderVideo);
	glutTimerFunc(66, RenderTime, 0);

	glutMainLoop();
#endif
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CAgoraOpenGLTexture* CAgoraOpenGLTexture::m_pAgoraOpenGlTexture = nullptr;
CLock CAgoraOpenGLTexture::m_lock;

CAgoraOpenGLTexture* CAgoraOpenGLTexture::getInstance(){
	if (nullptr == m_pAgoraOpenGlTexture){
		CAutoLock al(&m_lock);
		if (nullptr == m_pAgoraOpenGlTexture){
			m_pAgoraOpenGlTexture = new CAgoraOpenGLTexture;
		}
	}

	return m_pAgoraOpenGlTexture;
}

void CAgoraOpenGLTexture::releaseInstance(){
	if (nullptr != m_pAgoraOpenGlTexture){

		delete m_pAgoraOpenGlTexture;
		m_pAgoraOpenGlTexture = nullptr;
	}
}

CAgoraOpenGLTexture::CAgoraOpenGLTexture():
m_pBufferRenderTexture(NULL){

	m_pBufferRenderTexture = new uint8_t[0x800000];
	ZeroMemory(m_pBufferRenderTexture, 0x800000);
}

CAgoraOpenGLTexture::~CAgoraOpenGLTexture(){

	std::list<GLuint /*texture*/>::iterator it;
	for (it = mTextures.begin(); it != mTextures.end(); it++) {
		GLuint txt = *it;
		glDeleteTextures(1, &txt);
		mTextures.erase(it);
		break;
	}

	if (nullptr != m_pBufferRenderTexture){

		delete[] m_pBufferRenderTexture;
		m_pBufferRenderTexture = nullptr;
	}
}

int CAgoraOpenGLTexture::generateNativeTexture(){
	GLuint tex;

	glGenTextures(1, &tex);

	// TODO: query current active texture unit and bound texture and restore later
	//        glActiveTexture(GL_TEXTURE0);
	GLint oldTex = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, oldTex);

	mTextures.push_back(tex);

	return tex;
}

int CAgoraOpenGLTexture::updateTexture(GLuint texId, unsigned int uid){

	int nBufferLenOut = 0;
	int nWidth = 0;
	int nHeight = 0;
	if (CBufferMgr::getInstance()->popYUVBuffer(uid, m_pBufferRenderTexture, nBufferLenOut, nWidth, nHeight)){

		//        glActiveTexture(GL_TEXTURE0);
		GLint oldTex = 0;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTex);
		glBindTexture(GL_TEXTURE_2D, texId);
		//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nWidth * 4, nHeight * 4, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, m_pBufferRenderTexture);
		glBindTexture(GL_TEXTURE_2D, oldTex);

		int nystride = nWidth * 4;
		return (nystride<< 16 | nHeight);
	}

	return 0;
}

void CAgoraOpenGLTexture::deleteTexture(GLuint texId){
	std::list<GLuint /*texture*/>::iterator it;
	for (it = mTextures.begin(); it != mTextures.end(); it++) {
		if (*it == texId) {
			glDeleteTextures(1, &texId);
			mTextures.erase(it);
			break;
		}
	}
}