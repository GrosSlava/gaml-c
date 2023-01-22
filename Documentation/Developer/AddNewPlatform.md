# Add new platform

1. Add it into Core/CoreEnums.h/ETargetPlatform
2. Add it into Core/CompilerConfig.cpp/DEFAULT_TARGET_PLATFORM
3. Add it into OptionsParser.cpp/TargetPlatformOption
4. Add it into Backend/Platform/GenericPlatform.h
5. Implement your platform in Backend/Platform/YourPlatform/[YourPlatform].h
6. Add your extensions into Backend/Platform/PlatformHelperLibrary.h
