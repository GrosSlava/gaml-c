// This examples show features of enum declaration




/*
    Declare enum.
    Each enum is located on the stack (except the array of enum).
*/
enum EMyEnum(uint8) // enum can be inhereted from any integer type(by default uint32)
{
    var One;        // each field is number
    var Two = 3;    // we can give custom number for field
    var Three;      // there will be 4

    ***
        // enum as a class can have methods, but only static
        @static
    ***
    func foo {}

    // all enum members are public, you can't change its access modifier
} // not need ';' unlike C

enum EMyStringEnum(string) // enum can be inhereted from string
{
    var One = "One";    // each field is string, so, we need to init it
    var Two = "Two";
    var Three = "Three";
}



func main
{
    var EMyEnum m; // create local variable with EMyEnum type

    m = EMyEnum::One; // get access to enum member
    EMyEnum::foo(); // call enum method

    EMyEnum::max(); // get enum max value member
    // EMyStringEnum::max(); // will not work with strtings

    EMyEnum::min(); // get enum min value member
    // EMyStringEnum::min(); // will not work with strtings

    EMyEnum::count(); // get count of enum fields
    

    /*
        we can iterate over enum members
    */
    foreach( var EMyEnum LEnumField in EMyEnum )  { } 
    foreach( var const string LEnumField in EMyStringEnum )  { } // we can use enum real type with this enum, string it is real type of EMyStringEnum

    /*
        we can check that number has enum member alias
    */
    2 in EMyEnum;
    "One" in EMyStringEnum;

    /*
        get enum alias as string for given number
    */
    EMyEnum::str(m);
}
