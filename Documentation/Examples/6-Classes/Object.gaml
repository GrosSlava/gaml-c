// This examples show features of object declaration


/*
    Declare object.
    Each object is located in the heap.
*/
object UMyObject // object can be inhereted only from interface(many) or other object(one)
{
    // declare object members
    // by default all members are public
    int32 A;        // by default uninitialized members contains trash
    float B = 5.6f; // we can give dafault value

    private int32 C; // set this member as private

    // components can be instantiated only in object
    UMyComponent Comp = UMyComponent();
    UMyComponent Comp2; // this component is not instantiated, so there will be None
    UMyComponent Comp3; // this component is instantiated in constructor

    ***
        // declare method, it is public
    ***
    public func foo {}

    ***
        @virtual // declare virtual function, which can be overridden by a child
    ***
    func bar {} 

    ***
        // default constructor(each object has empty constructor by default)
    ***
    func UMyObject { Comp3 = UMyComponent(); }
    ***
        // constructor overloading

        @param OtherObject: const UMyObject
    ***
    func UMyObject {}
    ***
        // constructor overloading
        
        @param A: int32
    ***
    func UMyObject { Comp3 = UMyComponent(); this->A = A; } // use keyword 'this' to get access the current instance fields
} // not need ';' unlike C


object UMyObject2(UMyObject)
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


// we don't need to use forward declaration unlike C
component UMyComponent { }

***
    /*
        static modifiers marks that this object can be instantiated only once,
        each new instance will be pointing to one object

        static modifier works only with object
    */
    @static
***
object UMyStaticObject
{

}

***
    /*
        same to UMyStaticObject, but you need to call UMySingletonObject::Get() method to get instance
    */
    @static
***
object UMySingletonObject
{
    private func UMySingletonObject {}

    ***
        @static

        @return Result: UMySingletonObject
    ***
    public func Get
    {
        static UMySingletonObject = UMySingletonObject();
        return UMySingletonObject;
    }
}




func main
{
    UMyObject A; // create local uninitialized variable which can contains any UMyObject child object
    static_assert(A is None); // each object variable is a pointer, we didn't create an instance of an object, so there will be None 

    A = UMyObject(5); // instantiate object
    A = UMyObject2(); // instantiate new object, old one will be garbage by garbage collector
    
    A->bar(); // call virtual method (UMyObject2 version will be call)

    UMyObject B(A); // create new object which is a deep copy of A
    B = A; // B points to same object as A
    B = None; // now B is invalid


    // after losing all references to an instance of an object, it will be garbage by garbage collector
}