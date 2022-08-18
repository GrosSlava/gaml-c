
// This examples show features of functions implementation


func void bar(uint8 a, const string s) {}



func uint8 foo() 
[
    // here we can write static code that is executed at compile time every time the function is used
];

func uint8 foo()
//[
    // as we already have function declaration, we can't override static code
//]
{
    // here we can write function implementation body

    // we can declare local variable with default value, by default variable contains trash
    uint8 A = 8; 
    uint8 B = 0x5a; // 0x5A
    uint8 C = 11101b; 
    float f = 55.01f;
    double ff = 55.01;
    float SmallNumber = 12.e-5f;
    char c = 'H'; // gaml is case sensitive language (C != c)
    char NewLine = '\n';
    string s = "Hello World!\n";
    bool b = true; // false

    /*
        Static local variables are visible only inside function body, but created only once.
    */
    static uint8 StaticInt = 7;

    /*
        We can create local alias for type.
    */
    using MyUnsignedType = uint8;
    MyUnsignedType LVariable = 1;


    // we can't use local nested namespaces { {} } unlike c++

    // we can call other function
    bar(99, "Bla-bla-bla");
    

    // all operations must end with ';'

    /*
        Operators:

        a < b - less
        a > b - greather
        a <= b - less or equal
        a >= b - greather or equal
        a == b - equal
        a != b - not equal
        a && b - and
        a || b - or
        !a - not

        a & b - binary and
        a | b - binary or
        ~a - binary inverse
        a ^ b- binary xor
        a << b - binari shift left
        a >> b - binary shift right

        a + b - plus
        a - b - minus
        a * b - multiply
        a / b - divide
        a++ - increment (no ++a unlike C)
        a-- - decrement (no --a unlike C)
        a % b - mod
        a ^^ b - power
        a = b - assign
        a += b - equals to a = a + b
        a -= b - equals to a = a - b
        a *= b - equals to a = a * b
        a /= b - equals to a = a / b
        a %= b - equals to a = a % b
        a ^^= b - equals to a = a ^^ b
        a &= b - equals a = a & b
        a |= b - equals to a = a | b
        a ^= b - equals to a = a ^ b
        a <<= b - equals to a = a << b
        a >>= b - equals to a = a >> b

        a ? b : c - ternary operator, can be read as "if a then b else c"

        sizeof(a) - count of bits of type size of object/type
        typeof(a) - type of object/type
        nameof(a) - compile name of object/type
        alignof(a) - memory align of object/type
        isfunction(a) - check that object/type is function
        issubclass(a, b) - check that object/type a is subclass of object/type b
        isinstance(a, B) - check that object/type a is instance of type b
        addr(a) - get addres of object (return type is addr_t)

        a::b - access b from namespace a

        a in b - check that b contains a (for classes - address of a)
        a is b - check that object a is deep copy of b (useful for class objects), for default types (int32, bool etc.) '==' and 'is' are equal
        a is B - check that a is subclass of B, where B is class name. Same to issubclass(a, B)
    */
    // we can change operations sequence by ()


    /*
        We can cast one type to other.
        cast<|to_type|>(object)
    */
    uint16 CastedChar = cast<|uint16|>('H');
    /*
        It is unsafe cast because we may lost data.
        Default cast will throw error.
    */
    uint8 UnsafeCastedChar = unsafe_cast<|uint8|>('H');
    /*
        Compiler can try to convert one type to other. 
        If it is unsafe to cast one type to other, compiler will throw error.
    */
    uint16 AutoCastedChar = 'H';



    /*
        Gaml doesn't have exceptions.
        We can use only assert to check unlikable statements.
        Assert will generate runtime exception if expression is false.
    */
    assert(AutoCastedChar == 'H');
    /*
        Give error message.
    */
    assert(AutoCastedChar == 'H', "Assert triggered!");


    return 0; // each function must return a value (if its return type is not void)
}

