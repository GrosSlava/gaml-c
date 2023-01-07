# Functions overloading

Function overloading - it is feature to have more than 1 function with the same name, \
but with different number of arguments or/and types.



## Overloading works when

- Functions have differen count of arguments
- Functions have different argument types on same position
- Function has `const` modifier

### Example

```
func foo {}

***
	@param a: uint8
***
func foo {}

***
	@param a: string
***
func foo {}
```



## Selecting an overloaded function

Compiler will select function by inputs signature and modifiers (`const`) \
Compiler can call function if all function argument types match with all calling argument types. \
Compiler will try to use safe [cast](../2-Types/13-TypeCast.md) if can't find match function prototype.

### Scopes order

1. Scope specified by ('::' or '.' or '->')?
	1. Yes.
		Type that owns the function is class?
		1. Yes.
			1. Search in specified scope (success will stop search)
			2. Recursive search in parent scope (class can have max 1 parent(object)) (success will stop search)
			3. Error
		2. No.
			1. Search in specified scope (success will stop search)
			2. Error
	2. No.
		1. Search in current class (success will stop search)
		2. Search in current module (success will stop search)
		3. Search in global space (success will stop search)
		4. Error

### Algorithm

match = []
potential = []

Find potential functions:
1. Type that owns the function is const?
	1. Yes. 
		Function is const?
		1. Yes. 
			Signatures match?
			1. Yes.
				Add function to match.
			2. No.
				Signature has the same number of arguments?
				1. Yes.
					Add function to potential.
				2. No.
					Skip function.
		2. No.
			Skip function.
	2. No. 
		Function is not const?
		1. Yes. 
			Signatures match?
			1. Yes.
				Add function to match.
			2. No.
				Signature has the same number of arguments?
				1. Yes.
					Add function to potential.
				2. No.
					Skip function.
		2. No.
			Signatures match?
			1. Yes.
				Add function to potential.
			2. No.
				Signature has the same number of arguments?
				1. Yes.
					Add function to potential.
				2. No.
					Skip function.

Select function:
1. Match is empty?
	1. Yes.
		Potential is empty?
		1. Yes.
			Try to search in next scope.
		2. No.
			Type that owns the function is const?
			1. Yes.
				Has only 1 best match signature?
				1. Yes.
					Call it.
				2. No.
					Has 0 best match signature?
					1. Yes.
						Try to search in next scope.
					2. No.
						Error.
			2. No.
				Has only 1 best match non-const signature?
				1. Yes.
					Call it.
				2. No.
					Has 0 best match non-const signature?
					1. Yes.
						Has only 1 best match const signature?
						1. Yes.
							Call it.
						2. No.
							Has 0 best match const signature?
							1. Yes.
								Try to search in next scope.
							2. No.
								Error.
					2. No.
						Error.	
	2. No.
		Match count == 1?
		1. Yes.
			Call it.
		2. No.
			Error.

Best match: \
- Find signature with minimum count of safe-casted types to reach complete match
- Compile-time code of function allow call with given values
