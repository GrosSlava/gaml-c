// This examples show features of reflection in functions




/*
    For reflection we can use:
        sizeof(a)           --- count of bits of type size of object/type
        typeof(a)           --- type of object/type
        nameof(a)           --- compile name of object/type
        alignof(a)          --- memory align of object/type
        isfunction(a)       --- check that object/type is function
        isstruct(a)         --- check that object/type is struct
        isenum(a)           --- check that object/type is enum
        isinterface(a)      --- check that object/type is interface
        isobject(a)         --- check that object/type is object
        iscomponent(a)      --- check that object/type is component
        issubclass(a, b)    --- check that object/type a is subclass of object/type b
        isinstance(a, B)    --- check that object a is instance of type B
        isiterable(a)       --- check that object/type is isiterable
        isabstract(a)       --- check that object/type has abstract method
        addr(a)             --- get addres of object (return type is addr_t)
        default(a)          --- get default value for object, if function has default value for argument return it(e.g for integer it is 0)

    Predefined variables:
        string TARGET_PLATFORM  --- contains platform for which this code is build("Windows", "Linux")
        string TARGET_ARCH      --- contains cpu architecture for which this code is build("x86", "x86-64", "arm", "arm-64")
        bool DEBUG              --- true, if this is debug build
*/
