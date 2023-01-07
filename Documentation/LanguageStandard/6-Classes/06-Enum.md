# Enum

Enum - it is enumerated list of `static const` variables of same type. \
After optimizations enum can disappear from generated code.



## Enum features

1. Enum can be inhereted only from 1 [type](../2-Types/01-Types.md) to enumerate it (by default int32)
2. Enum is located in the same place as the parent type
3. Each field has the same type
4. Each field is `static const` and has default value
5. Enum can have only `static` methods
6. All enum members are `public`
7. Enum can't have [constructor](10-Constructor.md)
8. Enum is iterable type



## Enum declaration formula

```
***
[1-MODIFIERS]
***
[2-ACCESS_MODIFIER] enum [3-ENUM_NAME]([4-PARENT])
{
	[5-ENUM BODY]
}
```
1. [MODIFIERS](09-ClassModifiers.md) are a list of keywords to give a enum a special behaviour (can be empty or not exist)
2. ACCESS_MODIFIER is keyword to set enum visibility (optional)
3. ENUM_NAME is unique identifier which can contains only english alphabet letters, '_' and digits after first letter
4. Parent type to inherit (optional)
5. ENUM BODY is the namespace for variables and methods
6. NOTE: not need ';' at the end unlike C

### Enum body

- All members are always public
- All fields have the same type, so type in declaration not needed
- By default uninitialized members contains next value in enumarate list (available only for enumerable types)
- See [variable](../4-Variables/01-DeclareVariable.md) declaration
- See [method](../3-Functions/01-FunctionDeclaration.md) declaration
- See [operators overloading](07-OperatorsOverloading.md)

### Example

```
enum EMyEnum(uint8)
{
	// all enum members are public

	var Zero;       // for int start is 0
	var One;        // each field is number
	var Two = 3;    // we can give custom number for field
	var Three;      // there will be 4

	***
		@static
	***
	func foo {}
}
```

```
enum EMyStringEnum(string)
{
	// non - enumerable type should have default value for all fields

	var One = "One";
	var Two = "Two";
	var Three = "Three";
}
```



## Access to enum fields

Access to enum fields provides by '::' operator.

### Example

```
var EMyEnum m; // create local variable with EMyEnum type (m contains trash)
m = EMyEnum::One; // get access to enum member
EMyEnum::foo(); // call enum method
```



## Enum auto-generated methods

1. Get enum max value member (work with comparable types).
```
EMyEnum::max(); // EMyEnum::Three
// EMyStringEnum::max(); // will not work with strtings
```

2. Get enum min value member (work with comparable types).
```
EMyEnum::min(); // EMyEnum::Zero
// EMyStringEnum::min(); // will not work with strtings
```

3. Get count of enum fields.
```
EMyEnum::count(); // 4
```

4. Get name of enum field.
```
var EMyEnum m = EMyEnum::One;
EMyEnum::str(m); // "One"
```



## Iterate over enum

Enum is always iterable.

```
foreach( var EMyEnum LEnumField in EMyEnum ) { } 
foreach( var const string LEnumField in EMyStringEnum ) { }
```
