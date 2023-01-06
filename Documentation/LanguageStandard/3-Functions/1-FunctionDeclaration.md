# Function declaration

All executable code is described in functions. \
Unlike С, we can declare a function only once. \
**GAML** doesn't have forward declaration.



## Function declaration formula

```
***
    [1-MODIFIERS]
***
[2-ACCESS_MODIFIER] func [3-FUNCTION_NAME] [[4-Compile-time code]];
```
1. [MODIFIERS](3-FunctionModifiers.md) are a list of keywords to give a function a special behaviour (can be empty or not exist)
2. ACCESS_MODIFIER is keyword to set function visibility (optional)
3. FUNCTION_NAME is unique identifier which can contains only english alphabet letters, '_' and digits after first letter
4. [Compile-time code](4-CompileTimeCode.md) is the code that must be executed every time this function is mentioned during compilation (optional)

### Function access modifiers

- `public` - set function to be visible anywhere
- `protected` - set function to be visible only in current package
- `private` - set function to be visible only in current module

### Example

```
***
	@param a: uint8
	@param b: uint8(5)
***
public func foo;
```
