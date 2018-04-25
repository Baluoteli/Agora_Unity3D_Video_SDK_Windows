*Read this in other languages: [English](README.md)*

这个开源示例项目演示了如何在unity上快速集成Agora视频SDK，实现多人视频连麦直播。
它是基于Window SDK 的二次封装。所以的接口都是c的方式提供给用户分为如下几个部分：

- 基本API： 媒体的初始化，参数设置，加入推出频道等。
 
- 事件通知： getMessageCount(获取当前消息数目)；getMessage(获取一条有效的通知数据)；

- 视频回掉：getRGBAVideoData，通过传入uid,获取有效的RGBA数据


本开源项目使用 **C++** 语言

## 运行示例程序
首先在 [Agora.io 注册](https://dashboard.agora.io/cn/signup/) 注册账号，并创建自己的测试项目，获取到 App ID。将 APP_ID宏定义内容改为刚才申请的 App ID

程序提供了x86和x64位两套库，客户针对不同的应用环境选择不同的库，agora_sdk_c_wrapper.h包含所有的api的函数说明.


## 联系我们

- 完整的 API 文档见 [文档中心](https://docs.agora.io/cn/)
- 如果在集成中遇到问题，你可以到 [开发者社区](https://dev.agora.io/cn/) 提问
- 如果有售前咨询问题，可以拨打 400 632 6626，或加入官方Q群 12742516 提问
- 如果需要售后技术支持，你可以在 [Agora Dashboard](https://dashboard.agora.io) 提交工单
- 如果发现了示例代码的bug，欢迎提交 [issue](https://github.com/AgoraIO/OpenLive-Windows/issues)

## 代码许可

The MIT License (MIT).
