# Operator for

`for` is complex operator. \
It executes the code inside the brackets a certain number of times.

Same to "for" in c/c++, but **GAML** doesn't have version without brackets.

`for` operator has `static` version.

### Example

```
for( var int32 i = 0; i < 999; i++ )
{
	// 'for' scope

	// break - exit for
	// continue - go to the next iteration
}
// here 'i' is inaccessible, because it declared in 'for' scope
```

```
// Interesting case
for( var int32 i = 0, var int32 j = 0; i + j < 999; do { i++; j++; } )
{
	
}
```

```
/*
	Compile time for.
	Body of this 'for' will be interpreted during compile time and will be converted into code.
	e.g copy body code N times
*/
static for( var int32 i = 0; i < 999; i++ )
{

}
```
