#include "AgoraUilc.h"
#include "agora_sdk_c_wrapper.h"
#include "ExtendVideoFrameObserver.h"

#include "AgoraObject.h"
#include "MsgList.h"
#include "CBufferMgr.h"
#include "AgoraOpenGl.h"
using namespace AgoraSdkCWrapperUtilc;

CAgoraObject* gPAgoraObject = nullptr;
CFifoCmd* gPFifoCmd = nullptr;
CBufferMgr* gPBufferMgr = nullptr;
CAgoraOpenGl* gPOpenGl = nullptr;
CAgoraOpenGLTexture *gPOpenGlTexture = nullptr;
CExtendVideoFrameObserver* gPVideoObserver = nullptr;

AgoraSdkCWrapperUtilc::CFileIO AgoraSdkCWrapperUtilc::gFileSDK;
std::string AgoraSdkCWrapperUtilc::gStrInstance = "AgoraSdkWrapper";

void createEngine(const char *appId){

	std::string logPath = CAgoraWrapperUtilc::getAbsoluteDir() + "SdkWrapper.log";
	gFileSDK.openLog(logPath);
	gFileSDK.write(logPath);
	assert(0 < strlen(appId));
	if (nullptr != appId){

		gPAgoraObject = CAgoraObject::getAgoraInstance(appId);
		gPFifoCmd = CFifoCmd::getInstance();

		gPBufferMgr = CBufferMgr::getInstance();
		gPVideoObserver = new CExtendVideoFrameObserver;
		gPOpenGl = CAgoraOpenGl::getInstance();
		gPOpenGlTexture = CAgoraOpenGLTexture::getInstance();
	}
	return;
}

void deleteEngine(){

	if (gPAgoraObject){
		
		if (gPOpenGl){
			gPOpenGl->releaseInstance();
			gPOpenGl = nullptr;
		}

		if (gPOpenGlTexture){
			gPOpenGlTexture->releaseInstance();
			gPOpenGlTexture = nullptr;
		}

		if (gPVideoObserver){
			delete gPVideoObserver;
			gPVideoObserver = nullptr;
		}

		CAgoraObject::releaseAgoraInstance();
		gPAgoraObject = nullptr;
	}

	gFileSDK.close();
}

const char *getSdkVersion(){
	
	if (gPAgoraObject){

		return gPAgoraObject->getSDKVersion();
	}
}

const char *getMediaEngineVersion(){

	if (gPAgoraObject){

		return gPAgoraObject->getSDKVersion();
	}
}

void *getNativeHandle(){

	if (gPAgoraObject)
		return gPAgoraObject->getRtcEngine();
}

int joinChannel(const char *channelKey, const char *channelName, const char *info, unsigned int uid){
	
	if (gPAgoraObject)
		return gPAgoraObject->JoinChannel(channelKey, channelName, info, uid);
}

int leaveChannel(){

	if (gPAgoraObject)
		return gPAgoraObject->leaveChannel();
}

int enableLastmileTest(){

	if (gPAgoraObject)
		return gPAgoraObject->enableLastmileTest(TRUE);
}

int disableLastmileTest(){

	if (gPAgoraObject)
		return gPAgoraObject->enableLastmileTest(FALSE);
}

int enableVideo(){
	
	if (gPAgoraObject)
		return gPAgoraObject->enableVideo(TRUE);
}

int disableVideo(){

	if (gPAgoraObject)
		return gPAgoraObject->enableVideo(FALSE);
}

int enableLocalVideo(int enabled){

	if (gPAgoraObject)
		return gPAgoraObject->enableLocalRender(TRUE);
}

int startPreview(){

	if (gPAgoraObject)
		return gPAgoraObject->localVideoPreview(nullptr, TRUE);
}

int startPreviewEx(HWND wnd){

	if (gPAgoraObject)
		return gPAgoraObject->localVideoPreview(wnd, TRUE);
}

int stopPreview(){

	if (gPAgoraObject)
		return gPAgoraObject->localVideoPreview(nullptr, FALSE);
}

int enableAudio(){

	if (gPAgoraObject)
		return gPAgoraObject->enableAudio(TRUE);
}

int disableAudio(){

	if (gPAgoraObject)
		return gPAgoraObject->enableAudio(FALSE);
}

int setParameters(const char *options){

	if (gPAgoraObject)
		return gPAgoraObject->setParameters(options);
}

char *getParameter(const char *parameter, const char *args){

	return 0;
}

char *getCallId(){

	return "";
}

int rate(const char *callId, int rating, const char *desc){

	return 0;
}

int complain(const char *callId, const char *desc){

	return 0;
}

int setEnableSpeakerphone(int enabled){

	return 0;
}

int isSpeakerphoneEnabled(){

	return 0;
}

int setDefaultAudioRoutetoSpeakerphone(int defaultToSpeaker){

	return 0;
}

int setSpeakerphoneVolume(int volume){

	return 0;
}

int enableAudioVolumeIndication(int interval, int smooth){

	if (gPAgoraObject)
		return gPAgoraObject->enableAudioVolumeIndication(interval, smooth);
}

int startAudioRecording(const char *filePath, int quality){

	if (gPAgoraObject)
		return gPAgoraObject->startAudioRecording(filePath, quality);
}

int stopAudioRecording(){

	if (gPAgoraObject)
		return gPAgoraObject->stopAudioRecording();
}

int startAudioMixing(const char *filePath, int loopback, int replace, int cycle, int playTime){

	if (gPAgoraObject)
		return gPAgoraObject->startAudioMixing(filePath, loopback, replace, cycle, playTime);
}

int stopAudioMixing(){

	if (gPAgoraObject)
		return gPAgoraObject->stopAudioMixing();
}

int pauseAudioMixing(){

	if (gPAgoraObject)
		return gPAgoraObject->pauseAudioMixing();
}

int resumeAudioMixing(){

	if (gPAgoraObject)
		return gPAgoraObject->resumeAudioMixing();
}

int adjustAudioMixingVolume(int volume){

	if (gPAgoraObject)
		return gPAgoraObject->adjustAudioMixingVolume(volume);
}

int getAudioMixingDuration(){

	if (gPAgoraObject)
		return gPAgoraObject->getAudioMixingDuration();
}

int getAudioMixingCurrentPosition(){

	if (gPAgoraObject)
		return gPAgoraObject->getAudioMixingCurrentPosition();
}

int setAudioMixingPosition(int pos){

	if (gPAgoraObject)
		return gPAgoraObject->setAudioMixingPosition(pos);
}

int startEchoTest(){

	if (gPAgoraObject)
		return gPAgoraObject->enableEchoTest(TRUE);
}

int stopEchoTest(){

	if (gPAgoraObject)
		return gPAgoraObject->enableEchoTest(FALSE);
}

int muteLocalAudioStream(int muted){

	if (gPAgoraObject)
		return gPAgoraObject->muteLocalAudioStream(muted);
}

int muteAllRemoteAudioStreams(int muted){

	if (gPAgoraObject)
		return gPAgoraObject->muteAllRemoteAudioStreams(muted);
}

int muteRemoteAudioStream(int uid, int muted){

	if (gPAgoraObject)
		return gPAgoraObject->muteRemoteAudioStream(uid, muted);
}

int switchCamera(){

	return 0;
}

int setVideoProfile(int profile, int swapWidthAndHeight){

	if (gPAgoraObject)
		return gPAgoraObject->setVideoProfile(profile, swapWidthAndHeight);
}

int muteLocalVideoStream(int muted){

	if (gPAgoraObject)
		return gPAgoraObject->muteLocalVideoStream(muted);
}

int muteAllRemoteVideoStreams(int muted){
	
	if (gPAgoraObject)
		return gPAgoraObject->muteAllRemoteVideoStreams(muted);
}

int muteRemoteVideoStream(int uid, int muted){

	if (gPAgoraObject)
		return gPAgoraObject->muteRemoteVideoStream(uid, muted);
}

int setLogFile(const char *filePath){

	if (gPAgoraObject)
		return gPAgoraObject->setLogFile(filePath);
}

int setLogFilter(unsigned int filter){

	if (gPAgoraObject)
		return gPAgoraObject->setLogFilter(filter);
}

int renewChannelKey(const char *channelKey){

	if (gPAgoraObject)
		return gPAgoraObject->renewChannelKey(channelKey);
}

int setChannelProfile(int profile){

	if (gPAgoraObject)
		return gPAgoraObject->setChannelProfile(profile);
}

int setClientRole(int role, const char *permissionKey){

	if (gPAgoraObject)
		return gPAgoraObject->setClientRole(role, permissionKey);
}

int enableDualStreamMode(int enabled){

	if (gPAgoraObject)
		return gPAgoraObject->enableDualStreamMode(enabled);
}

int setEncryptionMode(const char *encryptionMode){

	if (gPAgoraObject)
		return gPAgoraObject->setEncryptionMode(encryptionMode);
}

int setEncryptionSecret(const char *secret){

	if (gPAgoraObject)
		return gPAgoraObject->setEncryptionSecret(secret);
}

int setRemoteVideoStreamType(int uid, int streamType){

	if (gPAgoraObject)
		return gPAgoraObject->setRemoteVideoStreamType(uid, streamType);
}

int startRecordingService(const char *recordingKey){

	if (gPAgoraObject)
		return gPAgoraObject->startRecordingService(recordingKey);
}

int stopRecordingService(const char *recordingKey){

	if (gPAgoraObject)
		return gPAgoraObject->stopRecordingService(recordingKey);
}

int refreshRecordingServiceStatus(){

	if (gPAgoraObject)
		return gPAgoraObject->refreshRecordingServiceStatus();
}

int createDataStream(int reliable, int ordered){

	if (gPAgoraObject)
		return gPAgoraObject->createDataStream(reliable, ordered);
}

int sendStreamMessage(int streamId, const char *data){

	if (gPAgoraObject)
		return gPAgoraObject->sendStreamMessage(streamId, data);
}

int setRecordingAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall){

	if (gPAgoraObject)
		return gPAgoraObject->setRecordingAudioFrameParametersWithSampleRate(sampleRate, channel, mode, samplesPerCall);
}

int setPlaybackAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall){

	if (gPAgoraObject)
		return gPAgoraObject->setPlaybackAudioFrameParametersWithSampleRate(sampleRate, channel, mode, samplesPerCall);
}

int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall){

	if (gPAgoraObject)
		return gPAgoraObject->setMixedAudioFrameParameters(sampleRate, samplesPerCall);
}

int adjustRecordingSignalVolume(int volume){

	if (gPAgoraObject)
		return gPAgoraObject->adjustRecordingSignalVolume(volume);
}

int adjustPlaybackSignalVolume(int volume){

	if (gPAgoraObject)
		return gPAgoraObject->adjustPlaybackSignalVolume(volume);
}

int setHighQualityAudioParametersWithFullband(int fullband, int stereo, int fullBitrate){

	if (gPAgoraObject)
		return gPAgoraObject->setHighQualityAudioParametersWithFullband(fullband, stereo, fullBitrate);
}

int enableInEarMonitoring(int enabled){

	return 0;
}

int enableWebSdkInteroperability(int enabled){

	if (gPAgoraObject)
		return gPAgoraObject->enableWebSdkInteroperability(enabled);
}

int setVideoQualityParameters(int preferFrameRateOverImageQuality){

	if (gPAgoraObject)
		return gPAgoraObject->setVideoQualityParameters(preferFrameRateOverImageQuality);
}

int enableVideoObserver(){

	if (gPAgoraObject && gPVideoObserver){
		return gPAgoraObject->EnableExtendVideoCapture(TRUE, gPVideoObserver);
	}
}

int disableVideoObserver(){

	if (gPAgoraObject && gPVideoObserver){
		return gPAgoraObject->EnableExtendVideoCapture(FALSE, gPVideoObserver);
	}
}

int generateNativeTexture(){

	if (gPAgoraObject && gPOpenGlTexture)
		return gPOpenGlTexture->generateNativeTexture();

	return 0;
}

int updateTexture(int tex, unsigned int uid){

	if (gPAgoraObject && gPOpenGlTexture)
		return gPOpenGlTexture->updateTexture(tex, uid);

	return 0;
}

void deleteTexture(int tex){

	if (gPAgoraObject && gPOpenGlTexture)
		gPOpenGlTexture->deleteTexture(tex);
}

int getMessageCount(){

	if (gPFifoCmd){
		return gPFifoCmd->getCount();
	}
}

int getRGBAVideoData(UINT uid, unsigned char* pData, int &nBufferLen, int &nWidth, int &nHeight){

	if (gPAgoraObject && gPBufferMgr){

		return gPBufferMgr->popYUVBuffer(uid, pData, nBufferLen, nWidth, nHeight);
	}
}

char *getMessage(){

	if (gPFifoCmd){
		std::string msg = gPFifoCmd->popCmd();
		AgoraWriteLog("%s return %s", __FUNCTION__, msg.data());

		return _strdup(msg.data());
	}
}

void freeObject(void *obj){
	
	if (obj){
		free(obj);
	}
}
