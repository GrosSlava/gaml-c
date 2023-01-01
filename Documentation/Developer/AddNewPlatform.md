# Add new platform

1. Add it into Compiler/CompilerConfig.h/ETargetPlatform
2. Add it into Compiler/CompilerConfig.cpp/DEFAULT_TARGET_PLATFORM
3. Add it into Compiler/CompilerOptions.cpp/TargetPlatformOption
4. Add it into Platform/GenericPlatform.h
5. Implement your platform in Platform/[YourPlatform].h
6. Add your extensions into Platform/PlatformHelperLibrary.h