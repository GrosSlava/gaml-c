# Object

Object - it is nearest type to c++ classes. 



## Object features

- Object can be inhereted only from 1 other object and/or many [interfaces](04-Interface.md)
- Object located on the heap
- Can use `super` keyword to get access to parent object type



## Object declaration formula

```
***
[1-MODIFIERS]
***
[2-ACCESS_MODIFIER] object [3-OBJECT_NAME]([4-PARENTS LIST])
{
	[5-OBJECT BODY]
}
```
1. [MODIFIERS](09-ClassModifiers.md) are a list of keywords to give a object a special behaviour (can be empty or not exist)
2. ACCESS_MODIFIER is keyword to set object visibility (optional)
3. OBJECT_NAME is unique identifier which can contains only english alphabet letters, '_' and digits after first letter
4. List of parent types, separated by ',', to inherit them (optional)
5. OBJECT BODY is the namespace for variables and methods
6. NOTE: not need ';' at the end unlike C

### Object body

- By default all members are public
- By default uninitialized members contains trash
- See [variable](../4-Variables/01-DeclareVariable.md) declaration
- See [method](../3-Functions/01-FunctionDeclaration.md) declaration
- See [operators overloading](07-OperatorsOverloading.md)
- See [constructor](10-Constructor.md)

### Example

```
object UMyObject
{
	// by default uninitialized members contains trash
	var int32 A;

	// we can give dafault value        
	var float B = 5.6f; 

	// set this member as private
	private var int32 C; 

	// declare method, it is public
	public func foo {}

	// declare virtual method, which can be overridden by a child
	***
		@virtual 
	***
	func bar;
}

// implement object method 
func UMyObject::bar { }

// inherit from UMyObject
object UMyObject2(UMyObject)
{
	// we can declare method with the same name as parent method, but it is not virtual
	func foo {} 

	***
		@final
		@override 
		// override parent method and set it as final, which means that this method can't be overridden by child
	***
	func bar
	{
		super::bar(); // use parent method version
	} 
}
```



## Access to object fields

Access to object fields provides by '->' operator. \
Access to object `static` fields provides by '::' operator.

### Example

```
var UMyObject A; // create local uninitialized variable which can contains any UMyObject child object
A = UMyObject(5); // instantiate object
A = UMyObject2(); // instantiate new object, old one will be garbage by garbage collector

A->bar(); // call virtual method (UMyObject2 version will be call)
A->foo(); // call non-virtual method (UMyObject version will be call)
```



## Object creating

```
var UMyObject A; // A = None
A = UMyObject(5); // instantiate new object, will be created invisible variable with type UMyObject, after will be assign
var UMyObject B(); // instantiate new object with default constructor
var UMyObject C(5); // instantiate new object with custom constructor
```
