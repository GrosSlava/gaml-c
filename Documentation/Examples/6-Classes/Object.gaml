// This examples show features of object declaration


/*
    Declare object.
    Each object is located in the heap.
*/
object UMyObject // object can be inhereted only from interface(many) or other object(one)
{
    // declare object members
    int32 A;        // by default uninitialized members contains trash
    float B = 5.6f; // we can give dafault value

    private int32 C; // set this member as private

    // components can be instantiated only in object
    UMyComponent Comp = UMyComponent();
    UMyComponent Comp2; // this component is not instantiated, so there will be None
    UMyComponent Comp3; // this component is instantiated in constructor

private: // start private block, by default we are in the public block

    // declare method, it is public, but we not leave private block
    public func void foo() {}

public:

    // declare virtual function, which can be overridden by a child
    func virtual void bar() {} 

    // default constructor(each object has empty constructor by default)
    func void UMyObject() { Comp3 = UMyComponent(); }
    func void UMyObject(const UMyObject OtherObject) {}
    // constructor overloading
    func void UMyObject(int32 A) { Comp3 = UMyComponent(); this->A = A; } // use keyword 'this' to get access the current instance fields
} // not need ';' unlike C


object UMyObject2 : UMyObject 
{
    // func void bar() {} // we can't declare method with the same name as parent method

    // override parent methoad and set it as final, which means that this method can't be overridden by child
    func void bar() override final 
    {
        super::bar(); // use parent method version
    } 
}


// we don't need to use forward declaration unlike C
component UMyComponent { }


/*
    static modifiers marks that this object can be instantiated only once,
    each new instance will be pointing to one object

    static modifier works only with object
*/
static object UMyStaticObject
{

}

/*
    same to UMyStaticObject, but you need to call UMySingletonObject::Get() method to get instance
*/
static object UMySingletonObject
{
    private UMySingletonObject() {}

    public static func UMySingletonObject Get()
    {
        static UMySingletonObject = UMySingletonObject();
        return UMySingletonObject;
    }
}




func void main()
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