// operator foreach




func main
{

	var const string s = "Hello world";

	/*
		foreach is similar to "for( c : s )" in c++
		foreach works only with iterable objects
	*/
	foreach( var const char c in s )
	{
		// foreach namespace

		// break - exit foreach
		// continue - go to the next iteration
	}



	/*
		Compile time foreach.
		Body of this 'foreach' will be interpreted during compile time and will be converted into code.
		e.g copy code from body
	*/
	static foreach( var const char c in s )
	{
		
	}
}