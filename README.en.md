# Agora iOS Signaling Tutorial for Windows
*其他语言版本： [简体中文](README.md)*

The Agora Windows Sample App is an open-source demo that will help you get message chat integrated directly into your Windows applications using the Agora Signal SDK.

With this sample app, you can:

- Login into chat app
- Send point to point message and receive point to point message off line
- Display point to point history message
- Join channel
- Send channel message, receive channel message
- Leave channel
- Logout signal server

Agora Signal SDK supports Android / Web / MacOS. You can find demos of these platform here:

- Android: https://github.com/AgoraIO/Agora-Signaling-Tutorial-Android
- Web    : https://github.com/AgoraIO/Agora-Signaling-Tutorial-Web
- MacOS  : https://github.com/AgoraIO/Agora-Signaling-Tutorial-macOS-Swift
- IOS  : https://github.com/AgoraIO/Agora-Signaling-Tutorial-iOS-Swift
- Linux  : https://github.com/AgoraIO/Agora-Signaling-Tutorial-Linux
- Java   : https://github.com/AgoraIO/Agora-Signaling-Tutorial-Java


## Running the App
First, create a developer account at [Agora.io](https://dashboard.agora.io/signin/), and obtain an App ID.
Then select the editor in the test project, click App Certificate, and get the App Certificate according to the operation.
Update "Agora-Signaling-Tutorial-Windows/AgoraSignal.ini" with your App ID and App Certificate.

```
[BaseInfo]
AppID=
AppCertificatedId=
```

## Developer Environment Requirements
- win7以上
- Visual Studio 2013

## Operating Instructions
- 1.SDK Version 1.2.0801
- 2.You need to copy the agorasdk.dll file in the DLL directory of the SDK to the compiled executable directory (debug / release)

## Connect Us
- You can find full API document at [Document Center](https://docs.agora.io/en/)
- You can file bugs about this demo at [issue](https://github.com/AgoraIO/Agora-Signaling-Tutorial-Windows/issues)

## License
The MIT License (MIT).
