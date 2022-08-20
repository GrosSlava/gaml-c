// operator foreach



func void main()
{

    const string s = "Hello world";

    /*
        foreach is similar to "for( c : s )" in c++
        foreach works only with iterable objects
    */
    foreach( const char c in s )
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
    static foreach( const char c in s )
    {
        
    }
}