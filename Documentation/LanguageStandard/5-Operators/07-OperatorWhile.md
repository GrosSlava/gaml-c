# Operator while

`while` is complex operator. \
It executes the code inside brackets and stop by condition. \
The condition is checked before the loop.

Same to "while" in c/c++, but **GAML** doesn't have version without brackets.

`while` operator has `static` version.

### Example

```
var int32 a = 999;
while( a > 0 )
{
	// while scope

	// break - exit while
	// continue - go to the next iteration

	a--;
}
```

```
/*
	Compile time while.
	Body of this 'while' will be interpreted during compile time and will be converted into code.
*/
static while( a > 0 )
{

}
```
