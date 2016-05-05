# SourceSdk-ServerPlugin

This SDK was made to be used by the NoCheatZ 4 server plugin.
The purpose is to make one SDK that can work with any interface versions of any games that use the SourceSdk.
The game is detected at runtime rather than compile time.
By doing this, we don't need to download thousands of different SDKs with unused headers.
It is also compatible with pretty much any compiler you want to use because all libs are removed - except libprotobuf.
The drawback is it take a lot of effort to port your code to this SDK.
You only need to compile the SourceSdk.cpp, the libprotobuf project and the Interfaces/Protobuf .cc and .cpp files.

This project is using parts of source from AlliedModders hl2sdk and from the Valve's SourceSdk and from Google's Protobuf.

https://github.com/ValveSoftware/source-sdk-2013/blob/master/LICENSE
https://github.com/google/protobuf/blob/master/LICENSE
