#pragma once

#include "AgoraUilc.h"
class CExtendVideoFrameObserver :
	public agora::media::IVideoFrameObserver
{
public:
	CExtendVideoFrameObserver();
	~CExtendVideoFrameObserver();

	virtual bool onCaptureVideoFrame(VideoFrame& videoFrame);
	virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame);

private:
	UINT m_uUidSelf;

	LPBYTE				m_lpImageBufferLocal;
	LPBYTE				m_lpImageBufferRemote;

	AgoraSdkCWrapperUtilc::CFileIO m_fileLocalYUV;
	AgoraSdkCWrapperUtilc::CFileIO m_fileRemoteYUV;
};

