// This examples show features of main function signature declaration


/*
    Minimal main function. 
    Works on any subsystem.

    We do not recommend using this signature with extern_c.
*/
func void main()
{

}

/*
    Same to previous example, but can return success code.
*/
func int32 main()
{
    return 0;
}




/*
    Main function for Console subsystem.
*/
func int32 main(int32 argc, const array<|string|> argv)
{
    return 0;
}
// NOTE: Gaml not support wmain

/*
    Main function for Console subsystem, if you use extern_c.
    Gaml not have pointers to pointers as char arrays in C, so we can't use argv.
*/
func extern_c int32 main(int32 argc, any argv)
{
    const string LCmdLine = string::c_str(argv, argc);

    return 0;
}

/*
    Main function for Console subsystem with wide char command line, if you use extern_c.
    Gaml not have pointers to pointers as char arrays in C, so we can't use argv.

    This version of main not supported by all compilers. Be careful.
*/
func extern_c int32 wmain(int32 argc, any argv)
{
    const string LCmdLine = string::c_wstr(argv, argc);
    return 0;
}




import Windows

/*
    Minimal main function for Window subsystem.
*/
func int32 WinMain()
{
    return 0;
}

/*
    Main function for Window subsystem.
*/
func int32 WinMain(Windows::HINSTANCE hInstance, const array<|string|> CmdLine, int32 nCmdShow)
{
    return 0;
}
// NOTE: Gaml not support wWinMain

/*
    Main function for Window subsystem, if you use extern_c
*/
func extern_c stdcall int32 WinMain(Windows::HINSTANCE hInstance, Windows::HINSTANCE hPrevInstance, any CmdLine, int32 nCmdShow)
{
    const string LCmdLine = string::c_str(CmdLine);

    return 0;
}

/*
    Main function for Window subsystem with wide char command line, if you use extern_c
*/
func extern_c stdcall int32 wWinMain(Windows::HINSTANCE hInstance, Windows::HINSTANCE hPrevInstance, any CmdLine, int32 nCmdShow)
{
    const string LCmdLine = string::c_wstr(CmdLine);

    return 0;
}




/*
    Main function for dll.
*/
func extern_c stdcall bool DllMain(Windows::HINSTANCE hinstDLL, uint32 fdwReason, any lpvReserved)
{
    return true;
}