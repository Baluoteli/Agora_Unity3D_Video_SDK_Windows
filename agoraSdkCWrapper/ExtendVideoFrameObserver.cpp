#include "ExtendVideoFrameObserver.h"
#include "CBufferMgr.h"
#include "AgoraObject.h"

using namespace AgoraSdkCWrapperUtilc;

#include "libyuv.h"
#pragma comment(lib,"yuv.lib")
#pragma warning(disable:4099)

CExtendVideoFrameObserver::CExtendVideoFrameObserver() :m_uUidSelf(0)
{
	m_lpImageBufferLocal = new BYTE[0x800000];
	m_lpImageBufferRemote = new BYTE[0x800000];

	std::string strPathLocal = CAgoraWrapperUtilc::getAbsoluteDir() + "Localyuv.yuv";
	m_fileLocalYUV.openMedia(strPathLocal.data());

	std::string strPathRemote = CAgoraWrapperUtilc::getAbsoluteDir() + "RemoteYuv.yuv";
	m_fileRemoteYUV.openMedia(strPathRemote.data());
}

CExtendVideoFrameObserver::~CExtendVideoFrameObserver()
{
	m_fileRemoteYUV.close();
	m_fileLocalYUV.close();

	delete[] m_lpImageBufferLocal; 
	m_lpImageBufferLocal = nullptr;
	delete[] m_lpImageBufferRemote;
	m_lpImageBufferRemote = nullptr;

	m_uUidSelf = 0;
}

bool CExtendVideoFrameObserver::onCaptureVideoFrame(VideoFrame& videoFrame)
{
	DWORD dStart = GetTickCount();
	CAgoraWrapperUtilc::AgoraOutDebugStr(_T(__FUNCTION__));

#if 0
	std::string sPathYUV = CAgoraWrapperUtilc::getAbsoluteDir() + "123.yuv";
	FILE* hFileOpen = fopen(sPathYUV.data(), "w+");
	fwrite(videoFrame.yBuffer,1,videoFrame.yStride * videoFrame.height,hFileOpen);
	fwrite(videoFrame.uBuffer,1,videoFrame.uStride * videoFrame.height /2 ,hFileOpen);
	fwrite(videoFrame.vBuffer,1,videoFrame.vStride * videoFrame.height /2,hFileOpen);
	fclose(hFileOpen);
#endif

	if (0 == m_uUidSelf)
		m_uUidSelf = CAgoraObject::getAgoraInstance()->getMyselfUid();

	int nWidth = videoFrame.width;
	int nHeight = videoFrame.height;
	int nYStride = videoFrame.yStride;
	int nUStride = videoFrame.uStride;
	int nVStride = videoFrame.vStride;

#if 0
	memcpy_s(m_lpImageBufferLocal, nYStride * nHeight, videoFrame.yBuffer, nYStride*nHeight);
	memcpy_s(m_lpImageBufferLocal + nYStride * nHeight, nUStride * nHeight / 2, videoFrame.uBuffer, nUStride * nHeight / 2);
	memcpy_s(m_lpImageBufferLocal + nYStride * nHeight + nUStride * nHeight / 2, nVStride * nHeight / 2, videoFrame.vBuffer, nVStride * nHeight / 2);

	int nBufferLen = nWidth * nHeight * 3 / 2;
	//m_fileLocalYUV.write((char*)m_lpImageBufferLocal,nBufferLen);

	CBufferMgr::getInstance()->pushYUVBuffer(m_uUidSelf, (uint8_t*)m_lpImageBufferLocal, nBufferLen, nWidth, nHeight);
#endif;

	libyuv::I420ToARGB((uint8_t*)videoFrame.yBuffer, videoFrame.yStride,
								  (uint8_t*)videoFrame.uBuffer, videoFrame.uStride,
								  (uint8_t*)videoFrame.vBuffer, videoFrame.vStride,
								  m_lpImageBufferLocal,nWidth * 4,
								  nWidth,nHeight);
	int nBufferLen = nWidth * nHeight * 4;

#if 0
	uint8_t* pDestBuffer = new uint8_t[nWidth * nHeight * 3 / 2];
	ZeroMemory(pDestBuffer, nWidth * nHeight * 3 / 2);
	libyuv::RGBAToI420(m_lpImageBufferLocal,nWidth * 4,
		pDestBuffer,nYStride,
		pDestBuffer + nYStride * nHeight,nUStride,
		pDestBuffer+ nYStride * nHeight + nUStride * nHeight / 2,nVStride,
		nWidth,nHeight);
	m_fileLocalYUV.write((char*)pDestBuffer,nWidth * nHeight * 3 /2);
#endif

	m_fileLocalYUV.write((char*)m_lpImageBufferLocal,nBufferLen);
	CBufferMgr::getInstance()->pushYUVBuffer(m_uUidSelf, (uint8_t*)m_lpImageBufferLocal,nBufferLen,nWidth,nHeight);
	
#if 0
	SIZE_T nBufferSize = 0x800000;

	BOOL bSuccess = CVideoPackageQueue::GetInstance()->PopVideoPackage(m_lpImageBuffer, &nBufferSize);
	if (!bSuccess)
		return false;

	m_lpY = m_lpImageBuffer;
	m_lpU = m_lpImageBuffer + videoFrame.height*videoFrame.width;
	m_lpV = m_lpImageBuffer + 5 * videoFrame.height*videoFrame.width / 4;

	memcpy_s(videoFrame.yBuffer, videoFrame.height*videoFrame.width, m_lpY, videoFrame.height*videoFrame.width);
	videoFrame.yStride = videoFrame.width;
	
	memcpy_s(videoFrame.uBuffer, videoFrame.height*videoFrame.width / 4, m_lpU, videoFrame.height*videoFrame.width / 4);
	videoFrame.uStride = videoFrame.width/2;

	memcpy_s(videoFrame.vBuffer, videoFrame.height*videoFrame.width / 4, m_lpV, videoFrame.height*videoFrame.width / 4);
	videoFrame.vStride = videoFrame.width/2;

	videoFrame.type = FRAME_TYPE_YUV420;
	videoFrame.rotation = 0;

#endif

	DWORD dwEnd = GetTickCount();
	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("onCaptureVideoFrame : %u\n"),dwEnd - dStart);

	return FALSE;
}

bool CExtendVideoFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame)
{
	CAgoraWrapperUtilc::AgoraOutDebugStr(_T(__FUNCTION__));

	int nWidth = videoFrame.width;
	int nHeight = videoFrame.height;
	int nYStride = videoFrame.yStride;
	int nUStride = videoFrame.uStride;
	int nVStride = videoFrame.vStride;

#if 0
	memcpy_s(m_lpImageBufferRemote, nYStride * nHeight, videoFrame.yBuffer, nYStride*nHeight);
	memcpy_s(m_lpImageBufferRemote + nYStride * nHeight, nUStride * nHeight / 2, videoFrame.uBuffer, nUStride * nHeight / 2);
	memcpy_s(m_lpImageBufferRemote + nYStride * nHeight + nUStride * nHeight / 2, nVStride * nHeight / 2, videoFrame.vBuffer, nVStride * nHeight / 2);

	int nBufferLen = nWidth * nHeight * 3 / 2;
	m_fileRemoteYUV.write((char*)m_lpImageBufferRemote,nBufferLen);

	//CBufferMgr::getInstance()->pushYUVBuffer(uid, (uint8_t*)m_lpImageBufferRemote, nBufferLen, nWidth, nHeight);
#endif

	libyuv::I420ToRGBA((uint8_t*)videoFrame.yBuffer, videoFrame.yStride,
		(uint8_t*)videoFrame.uBuffer, videoFrame.uStride,
		(uint8_t*)videoFrame.vBuffer, videoFrame.vStride,
		m_lpImageBufferLocal, nWidth * 4,
		nWidth, nHeight);
	int nBufferLen = nWidth * nHeight * 4;
	//m_fileLocalYUV.write((char*)m_lpImageBufferLocal, nBufferLen);
	CBufferMgr::getInstance()->pushYUVBuffer(m_uUidSelf, (uint8_t*)m_lpImageBufferLocal, nBufferLen, nWidth, nHeight);

	return true;
}
