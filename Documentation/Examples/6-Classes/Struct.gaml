// This examples show features of struct declaration




***
    /*
        Declare struct.
        Each structure is located on the stack (except the array of struct).
    */

    @align(16) // set structure memory align
***
struct FMyStruct // struct can't be inhereted from any type
{
    // Declare struct members
    // by default all members are public
    var int32 A;        // by default uninitialized members contains trash
    var float B = 5.6f; // we can give dafault value

    private var int32 C; // set this member as private, protected modifier can't be used with structs

    // declare method, it is public
    public func foo {}

    // declare method without implementation
    func bar;

    ***
        // default constructor(each struct has empty constructor by default)
    ***
    func FMyStruct {}
    ***
        // constructor overloading

        @param OtherStruct: const FMyStruct
    ***
    func FMyStruct {}
    ***
        // constructor overloading

        @param A: int32
    ***
    func FMyStruct { this->A = A; } // use keyword 'this' to get access the current instance fields
} // not need ';' unlike C


***
    // implement struct method 
***
func FMyStruct::bar { }



func main
{
    var FMyStruct m; // create local variable with FMyStruct type
    m.A = 99; // access to struct member
    m.foo(); // call struct method

    m = FMyStruct(5); // here will be created invisible variable with type FMyStruct, after will be assign
    var FMyStruct m2(5); // create local wariable with custom constructor
    var FMyStruct m3 = FMyStruct(5); // same to m2 example, invisible variable will not be created
}