# Operators overloading

Operators overloading - it is implementing some methods with reserved names and signatures to change compiler default behaviour. \
Not all kinds of user types support operators overloading.

Some operators do not have a default implementation. So, its use may cause a compilation error.



## Operators overloading features

1. Operator must have special reserved name
2. Operator must have the necessary inputs and returns in a certain order (names of arguments do not matter)
3. Operator can have additional modifiers



## Operators for `struct`

Let AType - type of current struct. \
Let BType - any other (or same) type.

1. A = B; \
`Default` : field to field copy.
```
***
	@param B: const AType
***
func OpAssign
{
	// do stuff... this = B
}
``` 

2. A + B \
`No default`
```
***
	@param A: const AType
	@param B: const BType
	@return Result: AType
***
func OpPlus
{
	// do stuff... Result = A + B
}
```


3. A += B; \
`No default`
```
***
	@param B: const BType
***
func OpPlusAssign
{
	// do stuff... this + B
}
```

4. A++ \
`No default`
```
func OpIncrement
{
	// do stuff... this++
}
```

5. A - B \
`No default`
```
***
	@param A: const AType
	@param B: const BType
	@return Result: AType
***
func OpMinus
{
	// do stuff... Result = A - B
}
```

6. A -= B; \
`No default`
```
***
	@param B: const BType
***
func OpMinusAssign
{
	// do stuff... this - B
}
```

7. A-- \
`No default`
```
func OpDecrement
{
	// do stuff... this--
}
```

8. A * B \
`No default`
```
***
	@param A: const AType
	@param B: const BType
	@return Result: AType
***
func OpMultiply
{
	// do stuff... Result = A * B
}
```

9. A *= B; \
`No default`
```
***
	@param B: const BType
***
func OpMultiplyAssign
{
	// do stuff... this * B
}
```

10. A / B \
`No default`
```
***
	@param A: const AType
	@param B: const BType
	@return Result: AType
***
func OpDivide
{
	// do stuff... Result = A / B
}
```

11. A /= B; \
`No default`
```
***
	@param B: const BType
***
func OpDivideAssign
{
	// do stuff... this / B
}
```

12. A % B \
`No default`
```
***
	@param A: const AType
	@param B: const BType
	@return Result: AType
***
func OpModdiv
{
	// do stuff... Result = A % B
}
```

13. A %= B; \
`No default`
```
***
	@param B: const BType
***
func OpModdivAssign
{
	// do stuff... this % B
}
```

14. A ^^ B \
`No default`
```
***
	@param A: const AType
	@param B: const BType
	@return Result: AType
***
func OpPower
{
	// do stuff... Result = A ^^ B
}
```

15. A ^^= B; \
`No default`
```
***
	@param B: const BType
***
func OpPowerAssign
{
	// do stuff... this ^^ B
}
```

16. -A \
`No default`
```
***
	@param A: const AType
	@return Result: AType
***
func OpNegate
{
	// do stuff... Result = -A
}
```

17. A < B \
`No default`
```
***
	@param A: const AType
	@param B: const AType
	@return Result: bool
***
func OpLess
{
	// do stuff... Result = A < B
}
```

18. A <= B \
`No default`
```
***
	@param A: const AType
	@param B: const AType
	@return Result: bool
***
func OpLessEqual
{
	// do stuff... Result = A <= B
}
```

19. A > B \
`No default`
```
***
	@param A: const AType
	@param B: const AType
	@return Result: bool
***
func OpGreater
{
	// do stuff... Result = A > B
}
```

20. A >= B \
`No default`
```
***
	@param A: const AType
	@param B: const AType
	@return Result: bool
***
func OpGreaterEqual
{
	// do stuff... Result = A >= B
}
```

21. A == B \
`Default` : field to field '=='
```
***
	@param A: const AType
	@param B: const AType
	@return Result: bool
***
func OpEqual
{
	// do stuff... Result = A == B
}
```

22. A != B \
`Default` : not (A == B)
```
***
	@param A: const AType
	@param B: const AType
	@return Result: bool
***
func OpNotEqual
{
	// do stuff... Result = A != B
}
```

23. cast<|BType|>(A) \
`No default` \
BType != AType
```
***
	@return Result: BType
***
func OpToTypeSafe
{
	// do stuff... Result = convert A to bool
}
```

24. unsafe_cast<|BType|>(A) \
`No default` \
BType != AType
```
***
	@return Result: BType
***
func OpToTypeUnsafe
{
	// do stuff... Result = convert A to bool
}
```

25. Get first element for iteration \
`No default`
```
***
	@return Result: [any type]
***
func begin {}
```

26. Get next element for iteration \
`No default`
```
***
	@return Result: [any type]
***
func next {}
```

27. Get last element for stop iteration \
`No default`
```
***
	@return Result: [any type]
***
func end {}
```



## Operators for `struct`, `object`, `component`

1. Get iterator (struct with begin, next, end methods) \
`No default`
```
***
	@return Result: [iterable type]
***
func iterator {}
```

2. A[1] \
`No default`
```
***
	@param Index: int32
	@return Result: [any type]
***
func OpElementAccess {}
```

3. Get hash based on class. \
`No default`
```
***
	@return Result: int32
***
func hash {}
```

4. Get first element for enumerating \
`No default`
```
***
	@return Result: AType
***
func efirst {}
```

5. Get next element for enumerating \
`No default`
```
***
	@return Result: AType
***
func enext {}
```
