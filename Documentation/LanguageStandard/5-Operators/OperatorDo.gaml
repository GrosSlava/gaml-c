// operator do




func main
{   

	/*
		do is complex operator. It executes the code inside brackets and stop by condition.
		Condition check after loop. 
	*/

	/*
		Same to "do while" in c/c++, but we don't have version without brackets.
	*/
	var int32 a = 999;
	do
	{
		// break - exit do
		// continue - go to the next iteration

		// do namespace

		a--;
	} ( a > 0 )

	// do code inside brackets 1 iteration
	do { a = 999 }

	do
	{
		var uint8 G;
	}
	// here G is inaccessible, because it declared in do namespace

	// interesting case
	for( var int32 i = 0, var int32 j = 0; i < 999; do { i++; j--; } )
	{

	}
}