# Operator foreach

`foreach` is complex operator. \
It iterates over a given object.

`foreach` is similar to "for( c : s )" in c++. \
`foreach` works only with iterable objects.

`foreach` operator has `static` version.

### Example

```
var const string s = "Hello world";
foreach( var const char c in s )
{
	// foreach scope

	// break - exit foreach
	// continue - go to the next iteration
}
// here 'c' is inaccessible, because it declared in 'foreach' scope
```

```
/*
	Compile time foreach.
	Body of this 'foreach' will be interpreted during compile time and will be converted into code.
	e.g copy code from body
*/
static foreach( var const char c in s )
{
	
}
```
