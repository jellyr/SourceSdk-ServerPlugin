# SourceSdk-ServerPlugin

This SDK was made to be used by the [NoCheatZ 4](https://github.com/L-EARN/NoCheatZ-4) server plugin.

The purpose is to make one SDK that can work with *any* interface versions of *any* games that use the SourceSdk.
The game is detected at runtime rather than compile time :
* I/You can set the proxy functions using [std::function](http://en.cppreference.com/w/cpp/utility/functional/function)
* You don't have have to download the SDKs of the games you make your plugin for
* You save spacedisk by 500% AT LEAST.
* You can use any compiler.

BUT :
* SDKs changes a lot. Once a game change something in this SDK, all will change.
* No librarys means a bit more compile time and a bit more brain fuck with ABI changes.
* This SDK is not YET ready to be used. You will prefer to use [MetamodSource](https://www.metamodsource.net/) instead. If not, then you are like me : You NEED C++11, you NEED Visual Studio 2015 compatiblity and you NEED one build per system.

To use this Sdk, you only need to compile the SourceSdk.cpp, the libprotobuf project and the Interfaces/Protobuf .cc and .cpp files.
If your libprotobuf project doesn't comoile fine, remove the protobuf 2.50 directory and extract [the legacy build](https://github.com/google/protobuf/releases/tag/v2.5.0).

This project is using parts of source from [AlliedModders hl2sdk](https://github.com/alliedmodders/hl2sdk), itself using source from the [Valve's SourceSdk](https://github.com/ValveSoftware/source-sdk-2013), itself using source from [Google's Protobuf](https://github.com/google/protobuf/releases/tag/v2.5.0).

https://github.com/ValveSoftware/source-sdk-2013/blob/master/LICENSE
https://github.com/google/protobuf/blob/master/LICENSE
