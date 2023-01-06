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
