# Function modifiers

All modifiers must be listed in description block `*** .... ***`\
All function modifiers must start with '@'. 



> `@param` NAME : TYPE(DEFAULT_VALUE) \
> Add input argument to function. \
> NAME - Name of argument. \
> TYPE - Type of argument(can have `const` and `mut` modifiers). \
> DEFAULT_VALUE - Expression for argument default value (optional). \
> Can be used multiple. \
> Order is important.

### Example

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
> TYPE - Type of return(can have `const` modifier). \
> DEFAULT_VALUE - Expression for return default value (optional). \
> Can be used once. \
> Order is not important.

### Example

```
***
	@return Result: uint8(0)
***
func foo
{
	Result = 0; // set result, but not return from function
	return 0;   // each function can return a value (if its return type is not void)
}
```



> `@deprecated` \
> Mark function as deprecated. \
> When user try to call it in the code, it will cause a warning. \
> Can be used once. \
> Order is not important.

> `@static` \
> Mark function as static. \
> It has no effect in the global space, but it compiles successfully. \
> In the class namespace, this function can be accessed by the class name. \
> Can be used once. \
> Order is not important.

> `@inline` \
> Mark function as inline. \
> With size optimization this modifier has no effect. \
> Without this modifier inlining will be selected by compiler. \
> Can be used once. \
> Order is not important.

> `@unimplemented` \
> Mark function as unimplemented. \
> This function can't have any realization and can't be called in code. \
> This function not appear in generated code. \
> Can be used once. \
> Order is not important.

> `@extern_c` \
> Marked function as extern_c. \
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