#include "AGEngineEventHandler.h"
#include "MsgList.h"

CAGEngineEventHandler::CAGEngineEventHandler() :m_pFifoCmd(nullptr)
{
	if (nullptr == m_pFifoCmd){
		m_pFifoCmd = CFifoCmd::getInstance();
	}
}

CAGEngineEventHandler::~CAGEngineEventHandler()
{
	if (nullptr != m_pFifoCmd){
		CFifoCmd::releaseInstance();
		m_pFifoCmd = nullptr;
	}
}

void CAGEngineEventHandler::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed){
	
	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s(%s,%u,%u)"), _T(__FUNCTION__), CAgoraWrapperUtilc::s2cs(channel), uid, elapsed);
	AgoraWriteLog("%s: %s(%s,%u,%d)", "CAGEngineEventHandler", __FUNCTION__, channel, uid, elapsed);

	char szMsg[MAX_PATH] = { '\0' };
	sprintf_s(szMsg, "onJoinChannelSuccess\t%s\t%u\t%d", channel, uid, elapsed);

	postMsg(szMsg);
}

void CAGEngineEventHandler::onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed){

	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s(%s,%u,%u)"), _T(__FUNCTION__), CAgoraWrapperUtilc::s2cs(channel), uid, elapsed);
	AgoraWriteLog("%s: %s(%s,%u,%d)", "CAGEngineEventHandler", __FUNCTION__, channel, uid, elapsed);

	char szMsg[MAX_PATH] = { '\0' };
	sprintf_s(szMsg, "onRejoinedChannel\t%s\t%u\t%d", channel, uid, elapsed);

	postMsg(szMsg);
}

void CAGEngineEventHandler::onWarning(int warn, const char* msg){

	if (msg){

		CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s(%d,%s)"), _T(__FUNCTION__), warn, CAgoraWrapperUtilc::s2cs(msg));
		AgoraWriteLog("%s: %s(%d,%s)", "CAGEngineEventHandler", __FUNCTION__, warn,msg);

		char szMsg[MAX_PATH] = { '\0' };
		sprintf_s(szMsg, "onWarning\t%d\t%s", warn, msg);

		postMsg(szMsg);
	}
}

void CAGEngineEventHandler::onError(int err, const char* msg){

	if (msg){

		CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s(%d,%s)"), _T(__FUNCTION__), err, CAgoraWrapperUtilc::s2cs(msg));
		AgoraWriteLog("%s: %s(%d,%s)", "CAGEngineEventHandler", __FUNCTION__, err, msg);

		char szMsg[MAX_PATH] = { '\0' };
		sprintf_s(szMsg, "onError\t%d\t%s", err, msg);

		postMsg(szMsg);
	}
}

void CAGEngineEventHandler::onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost){


}

void CAGEngineEventHandler::onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume){

}

void CAGEngineEventHandler::onLeaveChannel(const RtcStats& stat){

	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s()"),_T(__FUNCTION__));
	AgoraWriteLog("%s: %s()", "CAGEngineEventHandler", __FUNCTION__);

	char szMsg[MAX_PATH ] = { '\0' };
	sprintf_s(szMsg, "onLeftChannel\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", stat.duration, stat.txBytes, stat.rxBytes, stat.txAudioKBitRate, stat.rxAudioKBitRate, stat.txVideoKBitRate, stat.rxVideoKBitRate, stat.users);
	
	postMsg(szMsg);
}

void CAGEngineEventHandler::onRtcStats(const RtcStats& stat){

}

void CAGEngineEventHandler::onMediaEngineEvent(int evt){


}

void CAGEngineEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState){

}

void CAGEngineEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState){

}

void CAGEngineEventHandler::onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole){

	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("onClientRoleChanged(%d,%d)"),oldRole,newRole);
	AgoraWriteLog("%s: %s(%d,%d)", "CAGEngineEventHandler", __FUNCTION__, oldRole,newRole);

	char szMsg[MAX_PATH] = { '\0' };
	sprintf_s(szMsg, "onClientRoleChanged\t%d\t%d", oldRole, newRole);

	postMsg(szMsg);
}

void CAGEngineEventHandler::onNetworkQuality(int quality){

}

void CAGEngineEventHandler::onFirstLocalVideoFrame(int width, int height, int elapsed){

}

void CAGEngineEventHandler::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed){

}
void CAGEngineEventHandler::onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed){

}

void CAGEngineEventHandler::onUserJoined(uid_t uid, int elapsed){

	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s(%u,%d)"), _T(__FUNCTION__), uid, elapsed);
	AgoraWriteLog("%s: %s(%u,%d)", "CAGEngineEventHandler", __FUNCTION__, uid, elapsed);

	char szMsg[MAX_PATH] = { '\0' };
	sprintf_s(szMsg, "onUserJoined\t%d\t%d", uid, elapsed);

	postMsg(szMsg);
}

void CAGEngineEventHandler::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason){

	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s(%u,%d)"), _T(__FUNCTION__), uid, reason);
	AgoraWriteLog("%s: %s(%u,%d)", "CAGEngineEventHandler", __FUNCTION__, uid, reason);

	char szMsg[MAX_PATH] = { '\0' };
	sprintf_s(szMsg, "onUserOffline\t%d\t%d", uid, reason);

	postMsg(szMsg);
}

void CAGEngineEventHandler::onUserMuteAudio(uid_t uid, bool muted){

}
void CAGEngineEventHandler::onUserMuteVideo(uid_t uid, bool muted){

}
void CAGEngineEventHandler::onApiCallExecuted(const char* api, int error){
	
	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s(%s,%d)"),_T(__FUNCTION__),CAgoraWrapperUtilc::s2cs(api),error);
	AgoraWriteLog("%s: %s(%s,%d)", "CAGEngineEventHandler", __FUNCTION__, api, error);

	char szMsg[MAX_PATH] = { '\0' };
	sprintf_s(szMsg, "onApiExecuted\t%s\t%d", api, error);

	postMsg(szMsg);
}

void CAGEngineEventHandler::onLocalVideoStats(const LocalVideoStats& stats){

}
void CAGEngineEventHandler::onRemoteVideoStats(const RemoteVideoStats& stats){

}
void CAGEngineEventHandler::onCameraReady(){

	CAgoraWrapperUtilc::AgoraOutDebugStr(_T("%s()"),_T(__FUNCTION__));
	AgoraWriteLog("%s: %s()", "CAGEngineEventHandler", __FUNCTION__);

	char szMsg[MAX_PATH] = { '\0' };
	sprintf_s(szMsg, "onCameraReady");

	postMsg(szMsg);
}

void CAGEngineEventHandler::onVideoStopped(){

}

void CAGEngineEventHandler::onConnectionLost(){

}

void CAGEngineEventHandler::onConnectionInterrupted(){

}

void CAGEngineEventHandler::onUserEnableVideo(uid_t uid, bool enabled){

}

void CAGEngineEventHandler::onStartRecordingService(int error){

}

void CAGEngineEventHandler::onStopRecordingService(int error){

}

void CAGEngineEventHandler::onRefreshRecordingServiceStatus(int status){

}

inline void CAGEngineEventHandler::postMsg(const std::string &msg)
{
	if (m_pFifoCmd){
		m_pFifoCmd->pushCmd(msg);
	}
}