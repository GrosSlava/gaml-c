// This examples show features of global functions specifiers




// Minimum function declaration without any specifiers.
// return is void
func foo {}

***
	@deprecated // This function marked as deprecated. So when we try to call it in the code, we will get a warning.
***
func foo2{}  

***
	@static // This function is static. It has no effect in the global space, but it compiles successfully.
***
func foo3 {}

***
	@inline // This function marked as inline. In speed optimization this function will be inlined to code.
***
func foo4 {}

***
	/*
		This function marked as unimplemented. So this function can't have any realization and can't be called in code.
		This function not appear in generated code.
		unimplemented modifier can be used for prototyping module interface when you want to mark some functions as unimplemented instead empty realization.
	*/
	@unimplemented
***
func foo5;

***
	/*
		This function is marked as extern_c. This is necessary to communicate with the code on C.
		Extern C functions can't have overloading and it's names conflict throw the modules. Be careful.
	*/
	@extern_c
***
func foo6 {}

***
	/*
		It is calling convention specifier. By default functions have generator-native convention.
		e.g for MSVC - cdecl.

		You can use only one convention from list:
			cdecl,
			stdcall,
			fastcall,
			thiscall
	*/
	@stdcall
***
func foo7 {}

***
	/*
		This function is marked as private. So this function can be called only inside this module.
		By default all functions are public.
	*/
***
private func foo8 {}




***
	// It is function specifier monster. Do not do that!

	@deprecated
	@static
	@extern_c
	@stdcall
	@inline
	@unimplemented

	@return Result: const uint8
***
public func BadFoo;

***
	// It is better, if your function is deprecated.

	@deprecated
	@extern_c
	@stdcall
	@inline

	@return Result: const uint8
***
func BadFoo2 { /* any working code */ return 0; }

***
	// It can be working, but wery rare code.

	@extern_c
	@stdcall
	@inline

	@return Result: const uint8
***
func BadFoo3 { return 0; }

***
	// Common code looks like.

	@inline

	@return Result: uint8
***
func GoodFoo { return 0; }


/* 
	function declaration formula:

	***
		// Function description

		[modifiers]

		[params]
		[return]
	***
	[access modifier] func foo;
*/
