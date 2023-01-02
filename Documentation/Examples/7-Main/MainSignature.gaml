// This examples show features of main function signature declaration




/*
    Minimal main function. 
    Works on any subsystem.

    We do not recommend using this signature with extern_c.
*/
func main
{

}

***
    // Same to previous example, but can return success code.
   
   @return Result: int32
***
func main
{
    return 0;
}



***
    // Main function for Console subsystem.

    @param argv: const array<|string|> 
    @return Result: int32
***
func main
{
    return 0;
}
// NOTE: Gaml not support wmain





import Windows;

***
    // Minimal main function for Window subsystem.

    @return Result: int32
***
func WinMain
{
    return 0;
}

***
    // Main function for Window subsystem.
    // We do not recommend using this signature with extern_c.

    @param hInstance: Windows::HINSTANCE
    @param CmdLine: const array<|string|>
    @param nCmdShow: int32
    @return Result: int32
***
func WinMain
{
    return 0;
}
// NOTE: Gaml not support wWinMain


***
    // Main function for dll.
    // NOTE: not supported by all platforms.

    @param hinstDLL: Windows::HINSTANCE
    @param fdwReason: uint32
    @param lpvReserved: addr_t
    @return Result: bool
***
func DllMain
{
    return true;
}