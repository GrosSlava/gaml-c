// operator while




func main
{   
    /*
        while is similar to c/c++, but we don't have version without brackets
    */
    var int32 a = 999;
    while( a > 0 )
    {
        // while namespace

        // break - exit while
        // continue - go to the next iteration

        a--;
    }

    /*
        Compile time while.
        Body of this 'while' will be interpreted during compile time and will be converted into code.
    */
    static while( a > 0 )
    {

    }
}