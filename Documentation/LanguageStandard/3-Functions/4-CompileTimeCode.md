# Compile-time code

Functions have got 2 parts: compile-time code, runtime code.

Compile-time code it is code which will be executet when function name is mentioned during compilation. \
This code can be written as common code. It will be interpreted by compiler.



## Compile-time

- Compile-time code can access only to current function arguments
- Compile time code can use other functions
- Errors during interpretation will break compilation

### Example

```
func foo
[
	static_message("Hello World!");
];
```
