// This examples show features of struct declaration


/*
    Declare struct.
    Each structure is located on the stack (except the array of struct).
*/
struct FMyStruct // struct can't be inhereted from any type
alignas(16) // set structure memory align
{
    // Declare struct members
    int32 A;        // by default uninitialized members contains trash
    float B = 5.6f; // we can give dafault value

    private int32 C; // set this member as private, protected modifier can't be used with structs

private: // start private block, by default we are in the public block

    // declare method, it is public, but we not leave private block
    public func void foo() {}

public:

    // declare method without implementation
    func void bar();

    // default constructor(each struct has empty constructor by default)
    func void FMyStruct() {}
    func void FMyStruct(const FMyStruct OtherStruct) { }
    // constructor overloading
    func void FMyStruct(int32 A) { this->A = A; } // use keyword 'this' to get access the current instance fields
} // not need ';' unlike C

// implement struct method 
func void FMyStruct::bar()
{

}



func void main()
{
    FMyStruct m; // create local variable with FMyStruct type
    m.A = 99; // access to struct member
    m.foo(); // call struct method

    m = FMyStruct(5); // here will be created invisible variable with type FMyStruct, after will be assign
    FMyStruct m2(5); // create local wariable with custom constructor
    FMyStruct m3 = FMyStruct(5); // same to m2 example, invisible variable will not be created
}