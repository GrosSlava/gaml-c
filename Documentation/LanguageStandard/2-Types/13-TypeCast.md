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

See [operators overloading](../6-Classes/07-OperatorsOverloading.md) for casts in user types.

1. `cast<|T|>(WHAT)` - safe cast object WHAT to T. \
Safe cast can convert WHAT to T if WHAT have safe method to convert to T.

For [class](../6-Classes/01-ClassSystem.md) cast can convert from child to parent.

### Example

```
var uint32 CastedChar = cast<|uint32|>('H');
```

2. `unsafe_cast<|T|>(WHAT)` - unsafe cast object WHAT to T. \
Unsafe cast can convert WHAT to T if there is any safe or unsafe way to do it (e.g. convert to other type who have method to convert to T).

For [class](../6-Classes/01-ClassSystem.md) unsafe_cast can convert from child to parent and from parent to child.

### Example

```
var uint8 UnsafeCastedChar = unsafe_cast<|uint8|>('H');
```



## Standard types cast behaviour

1. From any smaller signed int size to any larger signed int size
	- `safe`
	- `constructor` exists
2. From any larger signed int size to any smaller signed int size
	- `unsafe`
	- `constructor` exists
3. From any signed int to any unsigned int
	- `unsafe`
	- `constructor` exists
4. From any unsigned int to any signed int
	- `unsafe`
	- `constructor` exists
5. From any int to bool
	- `unsafe`
	- `constructor` exists
7. From bool to any int
	- `unsafe`
	- `constructor` exists
8. From any int to addr_t
	- `safe`
	- `constructor` exists
9. From addr_t to any int
	- `unsafe`
	- `constructor` exists
10. From any int <= 32-bit to float
	- `safe`
	- `constructor` exists
11. From any int > 32-bit to float
	- `unsafe`
	- `constructor` exists
12. From any int to double
	- `safe`
	- `constructor` exists
13. From addr_t to float
	- `unsafe`
	- `constructor` exists
14. From addr_t to double
	- `safe`
	- `constructor` exists
15. From float to double
	- `safe`
	- `constructor` exists
16. From double to float
	- `unsafe`
	- `constructor` exists
17. From int32 to char
	- `safe`
	- `constructor` exists
18. From char to int32
	- `safe`
	- `constructor` exists
19. From any int != int32 to char
	- `unsafe`
	- `constructor` exists
20. From char to int != int32
	- `unsafe`
	- `constructor` exists
21. From any to string
	- `not`
	- `constructor` does not exist
22. From string to any
	- `not`
	- `constructor` does not exist
23. From any != vector to any vector
	- `not`
	- `constructor` does not exist
24. From vector to any != vector
	- `not`
	- `constructor` not exists
25. From smaller vector dimension to larger vector dimension
	- `safe`
	- `constructor` exists
26. From larger vector dimension to smaller vector dimension
	- `unsafe`
	- `constructor` exists
