# Function modifiers

All modifiers must be listed in description block `*** .... ***` \
All function modifiers must start with '@'. \
Modifiers are not inherited.



> `@param` NAME : TYPE(DEFAULT_VALUE) \
> Add input argument to function. \
> NAME - Name of argument. \
> TYPE - Type of argument (can be `const`, `mut` modifiers). \
> DEFAULT_VALUE - Expression for argument default value (optional). \
> Can be used multiple. \
> Order is important.

```
***
	// Function argument 'a' is const, so 'a' is read only.
	@param a: const uint8
***
func foo1 {}
```

```
***
	// Function argument 'a' is mutable, so the passed argument will change when 'a' modified.
	@param a: mut uint8
***
func foo2 {}
```



> `@return` NAME : TYPE(DEFAULT_VALUE) \
> Set function return. \
> NAME - Name of return. \
> TYPE - Type of return (can be `const` modifier). \
> DEFAULT_VALUE - Expression for return default value (optional). \
> Can be used multiple. \
> Order is important.

```
***
	@return Result: uint8(0)
***
func foo1
{
	Result = 0; // set result, but not return from function
	return 0;   // each function can return a value
}

***
	@return Result1: uint8
	@return Result2: char
***
func foo2
{
	Result1 = 0;
	Result2 = 'g';
	return 0, 'g'; // return multiple values (must return all positions)
}

....

var uint8 A1 = foo1();

var uint8 A2;
var char B2;
A2, B2 = foo2();
// can't use any of: +=, -=...
// A2, B2 += foo2(); // error

A1 = foo1().Result
A1 = foo2().Result1
```



> `@deprecated` \
> Mark function as deprecated. \
> When user try to call it in the code, it will cause a warning. \
> Can be used once. \
> Order is not important.

> `@static` \
> Mark function as static. \
> It has no effect in the global space, but it compiles successfully. \
> In the class namespace, this function can be accessed by the class name and can't use `this` keyword. \
> Can be used once. \
> Order is not important.

> `@unimplemented` \
> Mark function as unimplemented. \
> This function can't have any realization and can't be called in code. \
> This function not appear in generated code. \
> Can be used once. \
> Order is not important.

> `@extern_c` \
> Mark function as extern_c. \
> It is necessary to communicate with the code on C. \
> Extern C functions can't have overloading and it's names conflict throw the modules. \
> Extern C function can't be used as class method. \
> Can be used once. \
> Order is not important.

> `@cdecl` \
> `@stdcall` \
> `@fastcall` \
> Set function calling convention. \
> By default functions have generator-native convention. e.g for MSVC, GCC - cdecl. \
> Can be used one of list. \
> Can be used once. \
> Order is not important.

> `@virtual` \
> Mark function as virtual. \
> Work only with class methods. \
> This function realization can be overridden by child class. \
> Already `virtual` function can't have this modifier. \
> Can't be used together with `override`, `abstract`. \
> Can be used once. \
> Order is not important.

> `@override` \
> Mark function as override for parent virtual. \
> Work only with class methods. \
> This function realization override parent virtual method. \
> Parent should have virtual function. \
> Can't be used together with `virtual`, `abstract`. \
> Can be used once. \
> Order is not important.

> `@abstract` \
> Mark function as abstract. \
> Work only with class methods. \
> This function is `virtual`, but can't have realization in current class. \
> Child class must override this function. \
> Parent can't have `virtual` function with same name. \
> Can't be used together with `virtual`, `override`, `final`. \
> Can be used once. \
> Order is not important.

> `@final` \
> Mark function as final for override. \
> Work only with class methods. \
> This function can't be overridden by child class. \
> Parent should have virtual function or this function should be `virtual`. \
> Can't be used together with `abstract`. \
> Can be used once. \
> Order is not important.

> `@const` \
> Mark function as constant. \
> Work only with class methods. \
> This function can't change its fields. \
> If this function is `virtual` then all children must have this modifier in the `override` method. \
> Can be used once. \
> Order is not important.
