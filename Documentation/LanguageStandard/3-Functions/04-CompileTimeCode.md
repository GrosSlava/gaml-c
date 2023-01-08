# Compile-time code

Functions have got 2 parts: compile-time code, runtime code.

Compile-time code it is code which will be executet when function name is mentioned during compilation. \
This code can be written as common code. It will be interpreted by compiler.



## Compile-time code features

1. Compile-time code can access only to current function arguments
2. Compile-time code can use other functions
3. Errors during interpretation will break compilation
4. Compile-time code may return bool (true/false) to indicate that this function is currently unavailable (can affect on function overloading)
5. By default compile-time code return true

### Example

```
func foo
[
	static_message("Hello World!");
	return true;
];
```
