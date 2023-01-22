// This examples show features of custom entry point main functions declaration




***
	/*
		Custom entry point can be any.
		Custom entry point should be extern_c.
	*/

	@extern_c
***
func CustomEntryPoint
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



***
	// In this case we will run C main function without compiler generated code.
	
	@extern_c

	@return Result: int32
***
func main
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



***
	// Override init and change module initialization sequence.

	@extern_c
***
func init
{
	// module1::InitModuleInternal();
	// module2::InitModuleInternal();

	// module1::InitModule();
	// module2::InitModule();
}

***
	// Override deinit and change module deinitialization sequence.

	@extern_c
***
func deinit
{
	// module1::DeinitModuleInternal();
	// module2::DeinitModuleInternal();

	// module1::DeinitModule();
	// module2::DeinitModule();
}