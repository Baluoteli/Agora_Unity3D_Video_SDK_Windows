# Agora_Unity3D_Video_SDK_Windows
*其他语言版本： [简体中文](README.zh.md)*

This open source sample project demonstrates how to quickly integrate the Agora Video SDK in unity to achieve a multiplayer video broadcast. 
 It is a two-time package based on the window SDK. So the interface is provided to the user in the way of C to be divided into the following parts: 

- Basic API: Media initialization, parameter settings, to join the launch channel. 
 
- Event Notification: Getmessagecount (get the current number of messages); GetMessage (get a valid notification data); 

- video back: getrgbavideodata, get valid RGBA data by passing in the UID 


This demo is written in **C++**
 

## Runs the sample program 
 First registers the account in [Agora.io registration] (https://dashboard.agora.io/cn/signup/), and creates own test project, obtains the APP ID. Changing the APP_ID macro definition content to the app id

 program that you just requested provides x86 and x64 bit two sets of libraries, where customers choose different libraries for different application environments, and Agora_sdk_c_wrapper.h contains function descriptions for all APIs. 
 
 
 
##Contact Us 

-complete API documentation See [Document Center] (https://docs.agora.io/cn/) 
-If you encounter problems with integration, you can ask a question to the [developer community] (https://dev.agora.io/cn/) 
-If there is a pre-sales consultation, you can call 400 632 6626, or join the official Q Group 12742516 questions 
-if you need post-sales technical support, you can submit a work order in [Agora Dashboard] (https://dashboard.agora.io) 
-If you find a bug in the sample code, Welcome to submit [Issue] (https://github.com/AgoraIO/OpenLive-Windows/issues) 
 
##Code License 

the mit License (mit). 
 
