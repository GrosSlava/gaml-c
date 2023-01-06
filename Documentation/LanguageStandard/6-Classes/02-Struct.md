# Struct

Struct - it is wrapper over data with bound methods. 



## Structure features

- Structure can't be inhereted from any class
- Structure located on the stack
- Passing structure to function as `const` can be optimized by passing by pointer



## Struct declaration formula

```
***
[1-MODIFIERS]
***
[2-ACCESS_MODIFIER] struct [3-STRUCT_NAME]
{
	[4-STRUCT BODY]
}
```
1. [MODIFIERS](09-ClassModifiers.md) are a list of keywords to give a struct a special behaviour (can be empty or not exist)
2. ACCESS_MODIFIER is keyword to set struct visibility (optional)
3. STRUCT_NAME is unique identifier which can contains only english alphabet letters, '_' and digits after first letter
4. STRUCT BODY is the namespace for variables and methods
5. NOTE: not need ';' at the end unlike C

### Structure body

- By default all members are public
- `protected` modifier can't be used with member
- By default uninitialized members contains trash
- See [variable](../4-Variables/01-DeclareVariable.md) declaration
- See [method](../3-Functions/01-FunctionDeclaration.md) declaration
- See [operators overloading](07-OperatorsOverloading.md)
- See [constructor](10-Constructor.md)

### Example

```
***
	@align(16)
***
public struct FMyStruct
{
	// by default uninitialized members contains trash
	var int32 A;

	// we can give dafault value        
	var float B = 5.6f; 

	// set this member as private, protected modifier can't be used with structs
	private var int32 C; 

	// declare method, it is public
	public func foo {}

	// declare method without implementation
	func bar;
}

// implement struct method 
func FMyStruct::bar { }
```



## Access to structure fields

Access to structure fields provides by '.' operator. \
Access to structure `static` fields provides by '::' operator.

### Example

```
var FMyStruct m; // create local variable with FMyStruct type (call constructor by default)
m.A = 99; // access to struct member
m.foo(); // call struct method
```



## Structure creating

```
var FMyStruct m; // create with default constructor
m = FMyStruct(5); // here will be created invisible variable with type FMyStruct, after will be assign
var FMyStruct m2(); // create with default constructor
var FMyStruct m3(5); // create local variable with custom constructor
```
