# Function implementation

If function doesn't have implementation either in current module file, 
or in the module implementation file or in a third-party library, there will be a linking error.



## Function has been declared

If function not declared in namespace it will cause compile error.

### Function implementation formula

```
***
	[1-MODIFIERS]
***
func [2-NAMESPACE]::[3-FUNCTION_NAME]
{
	[4-Code]
}
```
1. Implementation description must list all modifiers from the function declaration and no new ones can be added
2. NAMESPACE is name of namespace from which this function is implemented (optional)
3. Name of function for implementation
4. Function code

### Example

```
***
	@param a: uint8
	@param b: uint8(5)
***
func foo;

***
	@param a: uint8
	@param b: uint8
***
func foo {}
```
Given function prototype is stronger than realization. \
So we can't redefine default values or arguments names or compile-time code.



## Function was not declared

If namespace is not used then function will be declared in current namespace. \
See [function declaration](01-FunctionDeclaration.md).



## Implementation code

- **GAML** supports nested namespaces
- all operations must end with ';'
- local variable declared in the scope of the operator is invisible to the top-level scope
- when accessing a variable, the one closest to the current scope is selected

### Function calling formual

```
[1-NAMESPACE]::[2-FUNCTION_NAME]([3-PARAMS])
```
1. NAMESPACE is name of namespace from which call function, empty means from current namespace
2. FUNCTION_NAME - name of function to call
3. Passing arguments separated by ',' in the order they are described in the function declaration

### Example

```
***
	@param a: uint8
	@param b: char
***
func foo;

func bar
{
	foo(1, 'G');
}
```
