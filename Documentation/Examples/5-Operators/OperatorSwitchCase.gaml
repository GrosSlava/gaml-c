// operator switch/case




func main
{
    /*
        switch/case is similar to c/c++ switch/case, but cases don't need break at the end
    */
    int32 a = 5;
    switch( a )
    {
    case 1: 
    {
        a = 11;
    }
    case [2, 3]: // case 2 and 3
    {
        a = 51;
    }
    case [4 ... 10]: // case 4 to 10 (4, 5, 6, 7, 8, 9, 10)
    {
        a = 51;
    }
    case [11 ... 13, 17, 20 ... 22]: // case for (11, 12, 13, 17, 20, 21, 22)
    {
        a = 1;
    }
    default: // default case
    {
        a = 0;
    }
    }

    // switch/case works with strings
    const string s = "Hello";
    switch( s )
    {
    case "He":
    {
        // do smth
    }
    case ["llo", "o"]:
    {
        // do smth
    }
    case ["Hello"]:
    {
        // do smth
    }
    }

    // let us have an enum and we want to switch by all it's members
    // switch_all is similar to switch, but works only with enums 
    /*
    switch_all()
    {

    }
    */



    /*
        Compile time switch.
        Body of this 'switch' will be interpreted during compile time and will be converted into code.
        e.g select one case code from body
    */
    static switch( s )
    {

    }

    /*
        Compile time switch_all.
        Body of this 'switch_all' will be interpreted during compile time and will be converted into code.
        e.g select one case code from body
    */
    /*
    static switch_all( s )
    {

    }
    */
}