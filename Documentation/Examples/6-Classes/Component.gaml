// This examples show features of component declaration




/*
    Declare component.
    Each component is located in the heap.
*/
component UMyComponent // component can be inhereted only from interface(many) or other component(one)
{
    // declare component members
    // by default all members are public
    var int32 A;        // by default uninitialized members contains trash
    var float B = 5.6f; // we can give dafault value

    private var int32 C; // set this member as private

    ***
        // declare method, it is public
    ***
    public func foo {}

    ***
        @virtual // declare virtual function, which can be overridden by a child
    ***
    func bar {} 

    ***
        // default constructor(each component has empty constructor by default)
    ***
    func UMyComponent {}
    ***
         // constructor overloading
        @param OtherComponent: const UMyComponent
    ***
    func UMyComponent {}
    ***
        // constructor overloading
        @param A: int32
    ***
    func UMyComponent { this->A = A; } // use keyword 'this' to get access the current instance fields
} // not need ';' unlike C

component UMyComponent2(UMyComponent) 
{
    func bar {} // we can declare method with the same name as parent method, but it is not virtual

    ***
        @final
        @override // override parent methoad and set it as final, which means that this method can't be overridden by child
    ***
    func bar 
    {
        super::bar(); // use parent method version
    } 
}




func main
{
    UMyComponent A; // create local uninitialized variable which can contains any UMyComponent child object
    static_assert(A is None); // each component variable is a pointer, we didn't create an instance of a component, so there will be None 

    // A = UMyComponent(); // we can't get instance of UMyComponent, component can be instantiated only as object member
}