// This examples show features of component declaration


/*
    Declare component.
    Each component is located in the heap.
*/
component UMyComponent // component can be inhereted only from interface(many) or other component(one)
{
    // declare component members
    int32 A;        // by default uninitialized members contains trash
    float B = 5.6f; // we can give dafault value

    private int32 C; // set this member as private

private: // start private block, by default we are in the public block

    // declare method, it is public, but we not leave private block
    public func void foo() {}

public:

    // declare virtual function, which can be overridden by a child
    func virtual void bar() {} 

    // default constructor(each component has empty constructor by default)
    func void UMyComponent() {}
    func void UMyComponent(const UMyComponent OtherComponent) {}
    // constructor overloading
    func void UMyComponent(int32 A) { this->A = A; } // use keyword 'this' to get access the current instance fields
} // not need ';' unlike C

component UMyComponent2 : UMyComponent 
{
    // func void bar() {} // we can't declare method with the same name as parent method

    // override parent methoad and set it as final, which means that this method can't be overridden by child
    func void bar() override final 
    {
        super::bar(); // use parent method version
    } 
}



func void main()
{
    UMyComponent A; // create local uninitialized variable which can contains any UMyComponent child object
    static_assert(A is None); // each component variable is a pointer, we didn't create an instance of a component, so there will be None 

    // A = UMyComponent(); // we can't get instance of UMyComponent, component can be instantiated only as object member
}