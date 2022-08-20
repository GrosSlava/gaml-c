// This examples show features of custom entry point main functions declaration



/*
    Custom entry point can be any.
    Custom entry point should be extern_c.
*/
func extern_c void CustomEntryPoint(int32 MyArg)
{
    /*
        call modules initialization
    */
    init();

    // do anything...

    /*
        call modules deinitialization
    */
    deinit();
}




/*
    In this case we will run C main function without compiler generated code.
*/
func extern_c int32 main()
{
    /*
        call modules initialization
    */
    init();

    // do anything...

    /*
        call modules deinitialization
    */
    deinit();

    return 0;
}



/*
    Override init and change module initialization sequence.
*/
func extern_c void init()
{
    // module1::init_module_internal();
    // module2::init_module_internal();

    // module1::init_module();
    // module2::init_module();
}

/*
    Override deinit and change module deinitialization sequence.
*/
func extern_c void deinit()
{
    // module1::deinit_module_internal();
    // module2::deinit_module_internal();

    // module1::deinit_module();
    // module2::deinit_module();
}