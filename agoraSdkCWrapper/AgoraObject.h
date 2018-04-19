#ifndef __AGORAOBJECT_H__
#define __AGORAOBJECT_H__

class CAGEngineEventHandler;
#include <atlstr.h>

class CAgoraObject
{
public:
	~CAgoraObject();
	static CAgoraObject* getAgoraInstance(const std::string &strAppID = "");
	static void releaseAgoraInstance();

	UINT getMyselfUid(){ return m_nSelfUID; }

	//standard API
	const char* getSDKVersion();
	IRtcEngine* getRtcEngine();
	int JoinChannel(const char *channelKey, const char *channelName, const char *info, unsigned int uid);
	int leaveChannel();
	int enableLastmileTest(BOOL bEnable = TRUE);
	int enableVideo(BOOL bEnable = TRUE);
	int enableLocalRender(BOOL bEnable);
	int localVideoPreview(HWND hVideoWnd, BOOL bPreviewOn);
	int enableAudio(BOOL bEnable);
	int setParameters(const char* options);
	int enableAudioVolumeIndication(int interval, int smooth);
	int startAudioRecording(const char* filePath, int quality);
	int stopAudioRecording();
	int startAudioMixing(const char *filePath, int loopback, int replace, int cycle, int playTime);
	int stopAudioMixing();
	int pauseAudioMixing();
	int resumeAudioMixing();
	int adjustAudioMixingVolume(int volume);
	int getAudioMixingDuration();
	int getAudioMixingCurrentPosition();
	int setAudioMixingPosition(int pos);
	int enableEchoTest(BOOL bEnable);
	int muteLocalAudioStream(int muted);
	int muteAllRemoteAudioStreams(int muted);
	int muteRemoteAudioStream(int uid, int muted);
	int switchCamera();
	int setVideoProfile(int profile, int swapWidthAndHeight);
	int muteLocalVideoStream(int muted);
	int muteAllRemoteVideoStreams(int muted);
	int muteRemoteVideoStream(int uid, int muted);
	int setLogFile(const char *filePath);
	int setLogFilter(unsigned int filter);
	int renewChannelKey(const char *channelKey);
	int setChannelProfile(int profile);
	int setClientRole(int role, const char *permissionKey);
	int enableDualStreamMode(int enabled);
	int setEncryptionMode(const char *encryptionMode);
	int setEncryptionSecret(const char *secret);
	int setRemoteVideoStreamType(int uid, int streamType);
	int startRecordingService(const char *recordingKey);
	int stopRecordingService(const char *recordingKey);
	int refreshRecordingServiceStatus();
	int createDataStream(int reliable, int ordered);
	int sendStreamMessage(int streamId, const char *data);
	int setRecordingAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall);
	int setPlaybackAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall);
	int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);
	int adjustRecordingSignalVolume(int volume);
	int adjustPlaybackSignalVolume(int volume);
	int setHighQualityAudioParametersWithFullband(int fullband, int stereo, int fullBitrate);
	int enableInEarMonitoring(int enabled);
	int enableWebSdkInteroperability(int enabled);
	int setVideoQualityParameters(int preferFrameRateOverImageQuality);

	int EnableExtendVideoCapture(BOOL bEnable, IVideoFrameObserver* lpVideoFrameObserver);

protected:

	class CGraba{
	public:
		CGraba(){ ; }
		~CGraba(){
			if (nullptr != m_pAgoraObject){
				delete m_pAgoraObject;
				m_pAgoraObject = nullptr;
			}
		}
	};

private:
	CAgoraObject(const std::string &strAppID);

	std::string m_strAppID;
	IRtcEngine* m_lpAgoraEngine;
	UINT		m_nSelfUID;

	static CAgoraObject* m_pAgoraObject;
	static CGraba m_Graba;
	CAGEngineEventHandler* m_pAgEventHandle;
};

#endif