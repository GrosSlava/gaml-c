# Type cast

Types can be converted to each other in different ways.



## Cast ways

- Compiler auto convert
- Use type constructor
- Use cast



## Compiler auto convert

Compiler can try to convert one type to other if current type have method to convert into another type, \
and it is safe cast. Otherwise, a compilation error will occur.

### Example

```
var int32 A = 33;
var double B = A; 
```

```
var double A = 33.3;
var int32 B = A; // error
```



## Type constructor

Type can have constructor from another type. \
It will construct new object based on given and assign it into variable.

### Example

```
var double A = int32(33.3); // A = 33
```



## Cast

See [operators overloading](TODO) for casts in user types.

`cast<|T|>(WHAT)` - safe cast object WHAT to T. \
Safe cast can convert WHAT to T if WHAT have method to convert to T.

### Example

```
var uint32 CastedChar = cast<|uint32|>('H');
```

`unsafe_cast<|T|>(WHAT)` - unsafe cast object WHAT to T. \
Unsafe cast can convert WHAT to T if there is any way to do it. (e.g. copy part of bits)

### Example

```
var uint8 UnsafeCastedChar = unsafe_cast<|uint8|>('H');
```
