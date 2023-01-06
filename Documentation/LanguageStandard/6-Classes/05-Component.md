# Component

Component - it is same to [Object](03-Object.md) but with additional limitation. 



## Component features

- Component can be inhereted only from 1 other component and/or many [interfaces](04-Interface.md)
- Component located on the heap
- Can use `super` keyword to get access to parent component type
- Can be instantiated only as object member with default value or in object method with assigning into object field



## Componentct declaration formula

```
***
[1-MODIFIERS]
***
[2-ACCESS_MODIFIER] component [3-COMPONENT_NAME]([4-PARENTS LIST])
{
	[5-COMPONENT BODY]
}
```
1. [MODIFIERS](09-ClassModifiers.md) are a list of keywords to give a component a special behaviour (can be empty or not exist)
2. ACCESS_MODIFIER is keyword to set component visibility (optional)
3. COMPONENT_NAME is unique identifier which can contains only english alphabet letters, '_' and digits after first letter
4. List of parent types, separated by ',', to inherit them (optional)
5. COMPONENT BODY is the namespace for variables and methods
6. NOTE: not need ';' at the end unlike C

### Component body

- By default all members are public
- By default uninitialized members contains trash
- See [variable](../4-Variables/01-DeclareVariable.md) declaration
- See [method](../3-Functions/01-FunctionDeclaration.md) declaration
- See [operators overloading](07-OperatorsOverloading.md)
- See [constructor](10-Constructor.md)

### Example

```
component UMyComponent
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

// implement component method 
func UMyComponent::bar { }

// inherit from UMyComponent
component UMyComponent2(UMyComponent)
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



## Access to component fields

Access to component fields provides by '->' operator. \
Access to component `static` fields provides by '::' operator.



## Component creating

```
var UMyComponent A; // create local uninitialized variable which can contains any UMyComponent child object, A = None
// A = UMyComponent(); // can't get instance of UMyComponent, component can be instantiated only as object member
```
