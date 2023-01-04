// This examples show features of main functions declaration

module main; // main - it is reserved name of main module, by default all .gaml files are module 'main'
// program can't have more than one main module(or 2 modules with the same name)
// main module file can have any name, but we can't import 'main' module




/*
	It is reserved name of function, which is called at the begin of program, before main.
	For dll it called at first load.
*/
func init_module
{

}
//func init_module_internal {} // we can't override this function, it is reserved

/*
	It is reserved name of function, which is called at the end of program.
	For dll it called when unload.
*/
func deinit_module
{

}
//func deinit_module_internal {} // we can't override this function, it is reserved


/*
	It is entry point of program if we build this gaml file as executable.
	Signature depends on selected subsystem.
*/
func main
{

}




/*
	Program start pipeline:

	init: - compiler generated start code
		module1_init_module_internal: - compiler generated module initialization
		module2_init_module_internal:
		...
		module1_init_module: - our module init function
		module2_init_module: 
		...

	deinit: - compiler generated end code
		module1_deinit_module_internal: - compiler generated module deinitialization
		module2_deinit_module_internal:
		...
		module1_deinit_module: - our module deinit function
		module2_deinit_module: 
		...

	_start: - C entry point with system initialization(depends on selected subsystem and platform compiler)
		main: - C main(depends on selected subsystem)
			init:
			main_main: - our main function
			deinit:
*/

// NOTE: we can change the entry point
/*
	Program start pipeline with custom entry point:

	init: - compiler generated start code
		module1_init_module_internal: - compiler generated module initialization
		module2_init_module_internal:
		...
		module1_init_module: - our module init function
		module2_init_module: 
		...
		
	deinit: - compiler generated end code
		module1_deinit_module_internal: - compiler generated module deinitialization
		module2_deinit_module_internal:
		...
		module1_deinit_module: - our module deinit function
		module2_deinit_module: 
		...

	custom_entry_point: - our main function, we can call internal
*/

/*
	Program pipeline for dll(shared library)

	init: - compiler generated start code
		module1_init_module_internal: - compiler generated module initialization
		module2_init_module_internal:
		...
		module1_init_module: - our module init function
		module2_init_module: 
		...
		
	deinit: - compiler generated end code
		module1_deinit_module_internal: - compiler generated module deinitialization
		module2_deinit_module_internal:
		...
		module1_deinit_module: - our module deinit function
		module2_deinit_module: 
		...

	init - shared library initialization method
	deinit - shared library deinitialization method
*/