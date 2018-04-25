#ifndef __AGORA_SDK_C_WRAPPER_H__
#define __AGORA_SDK_C_WRAPPER_H__

#ifndef AGORA_DllExport
#define AGORA_DllExport __declspec(dllexport)
#else
#define AGORA_DllExport _declspec(dllimport)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

	//standard agora api
    AGORA_DllExport void createEngine(const char *appId);
    AGORA_DllExport void deleteEngine();
    AGORA_DllExport const char *getSdkVersion();
    AGORA_DllExport const char *getMediaEngineVersion();
    AGORA_DllExport void *getNativeHandle();
	AGORA_DllExport int joinChannel(const char *channelKey, const char *channelName, const char *info, unsigned int uid);
    AGORA_DllExport int leaveChannel();
    AGORA_DllExport int enableLastmileTest();
    AGORA_DllExport int disableLastmileTest();
    AGORA_DllExport int enableVideo();
    AGORA_DllExport int disableVideo();
	AGORA_DllExport int enableLocalVideo(int enabled);
    AGORA_DllExport int startPreview();
	AGORA_DllExport int startPreviewEx(HWND wnd);
    AGORA_DllExport int stopPreview();
    AGORA_DllExport int enableAudio();
    AGORA_DllExport int disableAudio();
    AGORA_DllExport int setParameters(const char *options);
    AGORA_DllExport char *getParameter(const char *parameter, const char *args);
    AGORA_DllExport char *getCallId();
    AGORA_DllExport int rate(const char *callId, int rating, const char *desc);
    AGORA_DllExport int complain(const char *callId, const char *desc);
    AGORA_DllExport int setEnableSpeakerphone(int enabled);
    AGORA_DllExport int isSpeakerphoneEnabled();
    AGORA_DllExport int setDefaultAudioRoutetoSpeakerphone(int defaultToSpeaker);
    AGORA_DllExport int setSpeakerphoneVolume(int volume);
    AGORA_DllExport int enableAudioVolumeIndication(int interval, int smooth);
    AGORA_DllExport int startAudioRecording(const char *filePath, int quality);
    AGORA_DllExport int stopAudioRecording();
    AGORA_DllExport int startAudioMixing(const char *filePath, int loopback, int replace, int cycle, int playTime);
    AGORA_DllExport int stopAudioMixing();
    AGORA_DllExport int pauseAudioMixing();
    AGORA_DllExport int resumeAudioMixing();
    AGORA_DllExport int adjustAudioMixingVolume(int volume);
    AGORA_DllExport int getAudioMixingDuration();
    AGORA_DllExport int getAudioMixingCurrentPosition();
    AGORA_DllExport int setAudioMixingPosition(int pos);
    AGORA_DllExport int startEchoTest();
    AGORA_DllExport int stopEchoTest();
    AGORA_DllExport int muteLocalAudioStream(int muted);
    AGORA_DllExport int muteAllRemoteAudioStreams(int muted);
    AGORA_DllExport int muteRemoteAudioStream(int uid, int muted);
    AGORA_DllExport int switchCamera();
    AGORA_DllExport int setVideoProfile(int profile, int swapWidthAndHeight);
    AGORA_DllExport int muteLocalVideoStream(int muted);
    AGORA_DllExport int muteAllRemoteVideoStreams(int muted);
    AGORA_DllExport int muteRemoteVideoStream(int uid, int muted);
    AGORA_DllExport int setLogFile(const char *filePath);
    AGORA_DllExport int setLogFilter(unsigned int filter);
    AGORA_DllExport int renewChannelKey(const char *channelKey);
    AGORA_DllExport int setChannelProfile(int profile);
    AGORA_DllExport int setClientRole(int role, const char *permissionKey);
    AGORA_DllExport int enableDualStreamMode(int enabled);
    AGORA_DllExport int setEncryptionMode(const char *encryptionMode);
    AGORA_DllExport int setEncryptionSecret(const char *secret);
    AGORA_DllExport int setRemoteVideoStreamType(int uid, int streamType);
    AGORA_DllExport int startRecordingService(const char *recordingKey);
    AGORA_DllExport int stopRecordingService(const char *recordingKey);
    AGORA_DllExport int refreshRecordingServiceStatus();
    AGORA_DllExport int createDataStream(int reliable, int ordered);
    AGORA_DllExport int sendStreamMessage(int streamId, const char *data);
    AGORA_DllExport int setRecordingAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall);
    AGORA_DllExport int setPlaybackAudioFrameParametersWithSampleRate(int sampleRate, int channel, int mode, int samplesPerCall);
    AGORA_DllExport int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall);
    AGORA_DllExport int adjustRecordingSignalVolume(int volume);
    AGORA_DllExport int adjustPlaybackSignalVolume(int volume);
    AGORA_DllExport int setHighQualityAudioParametersWithFullband(int fullband, int stereo, int fullBitrate);
    AGORA_DllExport int enableInEarMonitoring(int enabled);
    AGORA_DllExport int enableWebSdkInteroperability(int enabled);
    AGORA_DllExport int setVideoQualityParameters(int preferFrameRateOverImageQuality);

	//extend video/audio observer
    AGORA_DllExport int enableVideoObserver();
    AGORA_DllExport int disableVideoObserver();
    AGORA_DllExport int generateNativeTexture();
    AGORA_DllExport int updateTexture(int tex, unsigned int uid);
    AGORA_DllExport void deleteTexture(int tex);

	AGORA_DllExport int getRGBAVideoData(UINT uid, unsigned char* pData,int &nBufferLen,int &nWidth,int &nHeight);
    
    //MessageLoop
    AGORA_DllExport int getMessageCount();
    AGORA_DllExport char *getMessage();
    AGORA_DllExport void freeObject(void *obj);
    
#if defined(__cplusplus)
}
#endif

#endif
