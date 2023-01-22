# Expression operators

Operators priority can be changed by `()` operator

- a()                   --- call function or constructor
- a[i]                  --- access to element under the index

- a < b                 --- less
- a > b                 --- greather
- a <= b                --- less or equal
- a >= b                --- greather or equal
- a == b                --- equal
- a != b                --- not equal
- a && b                --- and
- a || b                --- or
- !a                    --- not

- a & b                 --- binary and
- a | b                 --- binary or
- ~a                    --- binary inverse
- a ^ b                 --- binary xor
- a << b                --- binary shift left
- a >> b                --- binary shift right

- a + b                 --- plus
- a - b                 --- minus
- +a                    --- positive
- -b                    --- negative
- a * b                 --- multiply
- a / b                 --- divide
- a++                   --- increment (no ++a unlike C)
- a--                   --- decrement (no --a unlike C)
- a % b                 --- mod
- a ^^ b                --- power

- a = b                 --- assign
- a += b                --- equals to a = a + b
- a -= b                --- equals to a = a - b
- a *= b                --- equals to a = a * b
- a /= b                --- equals to a = a / b
- a %= b                --- equals to a = a % b
- a ^^= b               --- equals to a = a ^^ b
- a &= b                --- equals a = a & b
- a |= b                --- equals to a = a | b
- a ^= b                --- equals to a = a ^ b
- a <<= b               --- equals to a = a << b
- a >>= b               --- equals to a = a >> b

- a ? b : c             --- ternary operator, can be read as "if a then b else c"

- a::b                  --- access b from namespace a

- a in b                --- check that b contains a (for classes - address of a)
- a is b                --- check that object a is deep copy of b (useful for class objects), for default types (int32, bool etc.) '==' and 'is' are equal

- sizeof(a)             --- count of bits of type size of object/type
- typeof(a)             --- type of object/type
- nameof(a)             --- compile name of object/type
- isfunction(a)         --- check that object/type is function
- isstruct(a)           --- check that object/type is struct
- isenum(a)             --- check that object/type is enum
- isinterface(a)        --- check that object/type is interface
- isobject(a)           --- check that object/type is object
- iscomponent(a)        --- check that object/type is component
- issubclass(a, b)      --- check that object/type a is subclass of object/type b
- isinstance(a, B)      --- check that object a is instance of type B
- isiterable(a)         --- check that object/type is iterable
- isenumerable(a)       --- check that object/type is enumerable
- isabstract(a)         --- check that object/type has abstract method
- isalias(A, B)         --- check that type A is alias for type B
- islambda(a)           --- check that object/type is lambda
- addr(a)               --- get addres of object (return type is addr_t)
- default(a)            --- get default value for object, if function has default value for argument return it(e.g for integer it is 0)

- cast<|A|>(a)          --- cast object a to type A
- unsafe_cast<|A|>(a)   --- unsafe cast object a to type A
