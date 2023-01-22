# Operator if/else

`if` is complex operator. \
It provides branch selection.

Same to "if" in c/c++, but **GAML** doesn't have version without brackets. \
Unlike c++, user can't declare variable inside `if`.

`if` operator has `static` version.

### Example

```
if( 5 == 5 )
{
	// if scope
}
elif( 3 == 3 )
{
	// elif scope
}
else
{
	// else scope
}
```

```
/*
	Compile time if.
	Body of this 'if' will be included if codition is true.
*/
static if( DEBUG )
{

}
```
