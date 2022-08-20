// This examples show features of global functions specifiers


/* 
    Minimum function declaration without any specifiers.
*/
func void foo() {}

/*
    This function marked as deprecated. So when we try to call it in the code, we will get a warning.
*/
deprecated func void foo2() {}  

/*
    This function is static. It has no effect in the global space, but it compiles successfully.
*/
static func void foo3() {}

/*
    This function marked as inline. In speed optimization this function will be inlined to code.
*/
func inline void foo4() {}

/*
    This function marked as unimplemented. So this function can't have any realization and can't be called in code.
    This function not appear in generated code.
    unimplemented modifier can be used for prototyping module interface when you want to mark some functions as unimplemented instead empty realization.
*/
func void foo5() unimplemented;

/*
    This function is marked as extern_c. This is necessary to communicate with the code on C.
    Extern C functions can't have overloading and it's names conflict throw the modules. Be careful.
*/
func extern_c void foo6() {}

/*
    It is calling convention specifier. By default functions have generator-native convention.
    e.g for MSVC - cdecl.

    You can use only one convention from list:
        cdecl,
        stdcall,
        fastcall,
        thiscall
    Make sure that the calling convention remains before the function type, unlike C.
*/
func stdcall void foo7() {}

/*
    This function is marked as private. So this function can be called only inside this module.
    By default all functions are public.
*/
private func void foo8() {}



/*
    It is function specifier monster. Do not do that!
*/
public deprecated static func extern_c stdcall inline const uint8 BadFoo() unimplemented;

/*
    It is better, if your function is deprecated.
*/
deprecated func extern_c stdcall inline const uint8 BadFoo2() { /* any working code */ return 0; }

/*
    It can be working, but wery rare code.
*/
func extern_c stdcall inline const uint8 BadFoo3() { return 0; }

/*
    Common code looks like.
*/
func inline uint8 GoodFoo() { return 0; }


/* 
    function declaration formula:
    [access modifier] [deprecated, static] func [left specifiers] void foo() [right specifiers];
*/
