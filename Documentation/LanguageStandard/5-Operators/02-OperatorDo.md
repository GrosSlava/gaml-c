# Operator do

`do` is complex operator. \
It executes the code inside brackets and stop by condition. \
The condition is checked after the loop.

Same to "do while" in c/c++, but **GAML** doesn't have version without brackets.

`do` operator has `static` version.

### Example

```
var int32 a = 999;
do
{
	// 'do' scope

	// break - exit do
	// continue - go to the next iteration

	a--;
} ( a > 0 )
```

```
// do code inside brackets 1 iteration (condition is optional)
do { a = 999 }
```

```
do
{
	var uint8 G;
}
// here G is inaccessible, because it declared in 'do' scope
```

```
// compile time version
static do
{

}
```
