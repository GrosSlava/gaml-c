# Program start pipeline

**GAML** has complex program start pipeline.



## Standard pipeline

- init: - compiler generated start code
	- module1_InitModuleInternal - compiler generated module initialization
	- module2_InitModuleInternal
	- ...
	- module1_InitModule - user module init function
	- module2_InitModule 
	- ...

- deinit: - compiler generated end code
	- module1_DeinitModuleInternal - compiler generated module deinitialization
	- module2_DeinitModuleInternal
	- ...
	- module1_DeinitModule - user module deinit function
	- module2_DeinitModule 
	- ...

- _start: - C entry point with system initialization(depends on selected subsystem and platform compiler)
	- main: - C main(depends on selected subsystem)
		- init
		- main_main - user main function
		- deinit



## DLL pipeline

- init: - compiler generated start code (shared library initialization method)
	- module1_InitModuleInternal - compiler generated module initialization
	- module2_InitModuleInternal
	- ...
	- module1_InitModule - user module init function
	- module2_InitModule
	- ...
	
- deinit: - compiler generated end code (shared library deinitialization method)
	- module1_DeinitModuleInternal - compiler generated module deinitialization
	- module2_DeinitModuleInternal
	- ...
	- module1_DeinitModule - user module deinit function
	- module2_DeinitModule 
	- ...

- DllMain: - entry point where user should call init and deinit
	- ...
	