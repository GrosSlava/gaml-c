// This examples show features of functions declaration


***
    /*
        This is function in global space. 
        We can't have more than 1 function with the same name, but it can be with different arguments in the same module.
    */
***
func foo() {}

// func foo() {} // there will be error

***
    // It is function overloading. When we call foo() - call version without params.

    @param a: uint8
***
func foo {}



***
    /*
        Here we declare function prototype, but not give realization.
        Unlike С, we can declare a function only once. Because we have module system with namespace.
    */
***
func foo2;

***
    /*
        Here we give function realization. We can do it in this module file or in module implementation file.
        If we do not give the function implementation either in this file, or in the module implementation file or in a third-party library, 
        there will be a linking error.
    */
***
func foo2 {}



***
    /*
        It is function with arguments where second have default value.
        Unlike С, all functions declarations should have arguments names,
        it is better for code reading, but not affect on code generation.
    */

    @param a: uint8
    @param b: uint8(5)
***
func foo3;

***
    /*
        Given function prototype is stronger than realization. 
        So we can't redefine default values or arguments names.
    */

    @param a: uint8
    @param b: uint8
***
func foo3 {}



***
    // Function argument 'a' is const, so 'a' is read only.

    @param a: const uint8
***
func foo4 {}

***
    // Function argument 'a' is mutable, so the passed argument will change when 'a' modified.

    @param a: mut uint8
***
func foo5 {}
