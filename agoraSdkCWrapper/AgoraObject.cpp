#include "AgoraUilc.h"
#include "AgoraObject.h"
#include "AGEngineEventHandler.h"

CAgoraObject* CAgoraObject::m_pAgoraObject = nullptr;
CAgoraObject::CGraba CAgoraObject::m_Graba;

CAgoraObject* CAgoraObject::getAgoraInstance(const std::string &strAppId /*= ""*/){
	if (nullptr == m_pAgoraObject){
		assert(0 < strAppId.length());
		m_pAgoraObject = new CAgoraObject(strAppId);
	}

	return m_pAgoraObject;
}

void CAgoraObject::releaseAgoraInstance(){
	if (nullptr != m_pAgoraObject){
		delete m_pAgoraObject;
		m_pAgoraObject = nullptr;
	}
}

CAgoraObject::CAgoraObject(const std::string &strAppID) :
m_pAgEventHandle(nullptr),
m_lpAgoraEngine(nullptr),
m_strAppID(strAppID)
{
	m_lpAgoraEngine = createAgoraRtcEngine();
	if (m_lpAgoraEngine){

		m_pAgEventHandle = new CAGEngineEventHandler;
		assert(m_pAgEventHandle);

		RtcEngineContext ctx;
		ctx.eventHandler = m_pAgEventHandle;
		ctx.appId = m_strAppID.data();
		m_lpAgoraEngine->initialize(ctx);
	}
}

CAgoraObject::~CAgoraObject()
{
	m_lpAgoraEngine->release();
	m_lpAgoraEngine = nullptr;

	if (m_pAgEventHandle){
		delete m_pAgEventHandle;
		m_pAgEventHandle = nullptr;
	}
}

const char* CAgoraObject::getSDKVersion()
{
	int nBuildNumber = 0;
	const char *lpszEngineVer = getAgoraRtcEngineVersion(&nBuildNumber);

	char szbuf[MAX_PATH] = { '\0' };
	sprintf_s(szbuf, "%s %d", lpszEngineVer, nBuildNumber);

	return szbuf;
}

IRtcEngine* CAgoraObject::getRtcEngine()
{
	return m_lpAgoraEngine;
}

int CAgoraObject::JoinChannel(const char *channelKey, const char *channelName, const char *info, unsigned int uid)
{
	int nRet = 0;

	
	LPCSTR lpStreamInfo = "{\"owner\":true,\"width\":640,\"height\":480,\"bitrate\":500}";
	nRet = m_lpAgoraEngine->joinChannel(channelKey, channelName, lpStreamInfo, uid);

	return nRet;
}

int CAgoraObject::leaveChannel()
{
	m_lpAgoraEngine->stopPreview();
	int nRet = m_lpAgoraEngine->leaveChannel();

	m_nSelfUID = 0;

	return nRet;
}

int CAgoraObject::enableLastmileTest(BOOL bEnable /*= TRUE*/)
{
	int nRet = 0;

	if (bEnable)
		nRet = m_lpAgoraEngine->enableLastmileTest();
	else
		nRet = m_lpAgoraEngine->enableLastmileTest();

	return nRet;
}

int CAgoraObject::enableVideo(BOOL bEnable /*= TRUE*/)
{
	int nRet = 0;

	if (bEnable)
		nRet = m_lpAgoraEngine->enableVideo();
	else
		nRet = m_lpAgoraEngine->disableVideo();

	return nRet;
}

int CAgoraObject::enableLocalRender(BOOL bEnable)
{
	int nRet = 0;

	AParameter apm(*m_lpAgoraEngine);

	if (bEnable)
		nRet = apm->setParameters("{\"che.video.local.render\":true}");
	else
		nRet = apm->setParameters("{\"che.video.local.render\":false}");

	return nRet;
}

int CAgoraObject::localVideoPreview(HWND hVideoWnd, BOOL bPreviewOn)
{
	int nRet = 0;

	if (bPreviewOn) {
		VideoCanvas vc;

		vc.uid = 0;
		vc.view = hVideoWnd;
		vc.renderMode = RENDER_MODE_TYPE::RENDER_MODE_HIDDEN;

		m_lpAgoraEngine->setupLocalVideo(vc);
		nRet = m_lpAgoraEngine->startPreview();
	}
	else
		nRet = m_lpAgoraEngine->stopPreview();

	return nRet;
}

int CAgoraObject::enableAudio(BOOL bEnable)
{
	int nRet = 0;

	if (bEnable)
		nRet = m_lpAgoraEngine->enableAudio();
	else
		nRet = m_lpAgoraEngine->disableAudio();

	return nRet;
}

int CAgoraObject::setParameters(const char* options)
{
	int nRet = 0;

	AParameter apm(*m_lpAgoraEngine);

	nRet = apm->setParameters(options);

	return nRet;
}

int CAgoraObject::enableAudioVolumeIndication(int interval, int smooth)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.enableAudioVolumeIndication(interval, smooth);

	return nRet;
}

int CAgoraObject::startAudioRecording(const char* filePath, int quality)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.startAudioRecording(filePath, (AUDIO_RECORDING_QUALITY_TYPE)quality);

	return nRet;
}

int CAgoraObject::stopAudioRecording()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.stopAudioRecording();

	return nRet;
}

int CAgoraObject::startAudioMixing(const char *filePath, int loopback, int replace, int cycle, int playTime)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.startAudioMixing(filePath, loopback, replace, cycle);

	return nRet;
}

int CAgoraObject::stopAudioMixing()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.stopAudioMixing();

	return nRet;
}

int CAgoraObject::pauseAudioMixing()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.pauseAudioMixing();

	return nRet;
}

int CAgoraObject::resumeAudioMixing()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.resumeAudioMixing();

	return nRet;
}

int CAgoraObject::adjustAudioMixingVolume(int volume)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.adjustAudioMixingVolume(volume);

	return nRet;
}

int CAgoraObject::getAudioMixingDuration()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.getAudioMixingDuration();

	return nRet;
}

int CAgoraObject::getAudioMixingCurrentPosition()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.getAudioMixingCurrentPosition();

	return nRet;
}

int CAgoraObject::setAudioMixingPosition(int pos)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setAudioMixingPosition(pos);

	return nRet;
}

int CAgoraObject::enableEchoTest(BOOL bEnable)
{
	int nRet = 0;

	if (bEnable)
		nRet = m_lpAgoraEngine->startEchoTest();
	else
		nRet  = m_lpAgoraEngine->stopEchoTest();

	return nRet;
}


int CAgoraObject::muteLocalAudioStream(int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteLocalAudioStream(muted);

	return nRet;
}

int CAgoraObject::muteAllRemoteAudioStreams(int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteAllRemoteAudioStreams(muted);

	return nRet;
}

int CAgoraObject::muteRemoteAudioStream(int uid, int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteRemoteAudioStream(uid, muted);

	return nRet;
}

int CAgoraObject::switchCamera()
{
	int nRet = 0;

	return nRet;
}

int CAgoraObject::setVideoProfile(int profile, int swapWidthAndHeight)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setVideoProfile((VIDEO_PROFILE_TYPE)profile,swapWidthAndHeight);

	return nRet;
}

int CAgoraObject::muteLocalVideoStream(int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteLocalVideoStream(muted);

	return nRet;
}

int CAgoraObject::muteAllRemoteVideoStreams(int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteAllRemoteVideoStreams(muted);

	return nRet;
}

int CAgoraObject::muteRemoteVideoStream(int uid, int muted)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.muteRemoteVideoStream(uid, muted);

	return nRet;
}

int CAgoraObject::setLogFile(const char *filePath)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setLogFile(filePath);

	return nRet;
}

int CAgoraObject::setLogFilter(unsigned int filter)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setLogFilter(filter);

	return nRet;
}

int CAgoraObject::renewChannelKey(const char *channelKey)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->renewChannelKey(channelKey);

	return nRet;
}

int CAgoraObject::setChannelProfile(int profile)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setChannelProfile((CHANNEL_PROFILE_TYPE)profile);

	return nRet;
}

int CAgoraObject::setClientRole(int role, const char *permissionKey)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setClientRole((CLIENT_ROLE_TYPE)role,permissionKey);

	return nRet;
}

int CAgoraObject::enableDualStreamMode(int enabled)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.enableDualStreamMode(enabled);

	return nRet;
}

int CAgoraObject::setEncryptionMode(const char *encryptionMode)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setEncryptionMode(encryptionMode);

	return nRet;
}

int CAgoraObject::setEncryptionSecret(const char *secret)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setEncryptionSecret(secret);

	return nRet;
}

int CAgoraObject::setRemoteVideoStreamType(int uid, int streamType)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setRemoteVideoStreamType(uid, (REMOTE_VIDEO_STREAM_TYPE)streamType);

	return nRet;
}

int CAgoraObject::startRecordingService(const char *recordingKey)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.startRecordingService(recordingKey);

	return nRet;
}

int CAgoraObject::stopRecordingService(const char *recordingKey)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.stopRecordingService(recordingKey);

	return nRet;
}

int CAgoraObject::refreshRecordingServiceStatus()
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.refreshRecordingServiceStatus();

	return nRet;
}

int CAgoraObject::createDataStream(int reliable, int ordered)
{
	int nRet = 0;

	int nStreamID = 0;
	nRet = m_lpAgoraEngine->createDataStream(&nStreamID, reliable, ordered);
	
	return nRet;
}

int CAgoraObject::sendStreamMessage(int streamId, const char *data)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->sendStreamMessage(streamId, data, strlen(data));

	return nRet;
}

int CAgoraObject::setRecordingAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setRecordingAudioFrameParameters(sampleRate, channel, (RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);

	return nRet;
}

int CAgoraObject::setPlaybackAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setPlaybackAudioFrameParameters(sampleRate, channel, (RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);

	return nRet;
}

int CAgoraObject::setMixedAudioFrameParameters(int sampleRate, int samplesPerCall)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setMixedAudioFrameParameters(sampleRate, samplesPerCall);

	return nRet;
}

int CAgoraObject::adjustRecordingSignalVolume(int volume)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.adjustRecordingSignalVolume(volume);

	return nRet;
}

int CAgoraObject::adjustPlaybackSignalVolume(int volume)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.adjustPlaybackSignalVolume(volume);

	return nRet;
}

int CAgoraObject::setHighQualityAudioParametersWithFullband(int fullband, int stereo, int fullBitrate)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setHighQualityAudioParameters(fullband, stereo, fullBitrate);

	return nRet;
}

int CAgoraObject::enableInEarMonitoring(int enabled)
{
	int nRet = 0;

	return nRet;
}

int CAgoraObject::enableWebSdkInteroperability(int enabled)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.enableWebSdkInteroperability(enabled);

	return nRet;
}

int CAgoraObject::setVideoQualityParameters(int preferFrameRateOverImageQuality)
{
	int nRet = 0;

	RtcEngineParameters rep(*m_lpAgoraEngine);

	nRet = rep.setVideoQualityParameters(preferFrameRateOverImageQuality);

	return nRet;
}

int CAgoraObject::EnableExtendVideoCapture(BOOL bEnable, IVideoFrameObserver* lpVideoFrameObserver)
{
	agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
	mediaEngine.queryInterface(m_lpAgoraEngine, INTERFACE_ID_TYPE::AGORA_IID_MEDIA_ENGINE);

	int nRet = 0;
	AParameter apm(*m_lpAgoraEngine);

	if (mediaEngine.get() == NULL)
		return FALSE;

	if (bEnable && lpVideoFrameObserver != NULL) {
		//apm->setParameters("{\"che.video.local.camera_index\":1024}");
		nRet = mediaEngine->registerVideoFrameObserver(lpVideoFrameObserver);
	}
	else {
		nRet = mediaEngine->registerVideoFrameObserver(NULL);
		apm->setParameters("{\"che.video.local.camera_index\":0}");
	}

	return nRet;
}
