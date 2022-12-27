// operator if/else




func main
{
    if( 5 == 5 )
    {
        // if namespace

        // break - go to the end of if
    }
    else if( 3 == 3 )
    {

    }
    else
    {
        // else namespace
    }

    /*
        if hasn't got version without brackets
    */
    int8 a;
    if( true ) { a = 5; }


    // we can't declare variable inside if, unlike c++
    //if( int32 LVar = 55 ) {}



    /*
        Compile time if.
        Body of this 'if' will be included if codition is true.
    */
    static if( DEBUG )
    {

    }
}