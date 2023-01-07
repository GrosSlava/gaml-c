# Interface

Interface - it is abstract class only with methods to implement.



## Interface features

1. Interface can be inhereted only from other interfaces(many)
2. Interface can't be instantiated
3. Interface can contains only abstract methods
4. Interface can't have a constructor



## Interface declaration formula

```
***
[1-MODIFIERS]
***
[2-ACCESS_MODIFIER] interface [3-INTERFACE_NAME]([4-PARENTS LIST])
{
	[5-INTERFACE BODY]
}
```
1. [MODIFIERS](09-ClassModifiers.md) are a list of keywords to give a interface a special behaviour (can be empty or not exist)
2. ACCESS_MODIFIER is keyword to set interface visibility (optional)
3. INTERFACE_NAME is unique identifier which can contains only english alphabet letters, '_' and digits after first letter
4. List of parent types, separated by ',', to inherit them (optional)
5. INTERFACE BODY is the namespace for methods
6. NOTE: not need ';' at the end unlike C

### Interface body

- By default all members are public
- `private` modifier can't be used with member
- See [method](../3-Functions/01-FunctionDeclaration.md) declaration

### Example

```
interface IMyInterface
{
	***
		// in interface we can declare only abstract methods, which will be overridden in object or component
		@abstract
	***
	func foo;
}
```



## Interface creating

```
var IMyInterface A; // create local uninitialized variable which can contains any IMyInterface child object, A = None
// A = IMyInterface(); // we can't get instance of interface
```
