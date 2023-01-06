
implement MyModule; // set that we are implementing a module, the name of this file must match the name of the implementing module

// can import other modules if module depends on them




***
	// Give function implementation.
***
func foo2 {}

***
	// Since we have a module header, and this function is not declared in the header, so this function will not be imported into another file.
***
func foo3 {}
