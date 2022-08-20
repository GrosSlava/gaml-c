// This examples show features of operators overloading


/*
    Only enum, struct can have overloaded operators.
    See example with struct.
*/


struct FMyStruct 
{

    /*
        Overloading binary operator. 
        Result will be new copy of struct.
    */
    func FMyStruct operator+(const FMyStruct A, const FMyStruct B)
    {
        FMyStruct LResult;

        // do stuff... LResult = A + B

        return LResult;
    }

    /*
        Overloading binary operator. 
        Result will be assign to this struct.
    */
    func void operator+(const FMyStruct B)
    {
        // do stuff... this + B
    }

    /*
        Overloading unary operator. 
        Result will be new copy of struct.
    */
    func FMyStruct operator++(const FMyStruct A)
    {
        FMyStruct LResult = A;
        // do stuff... LResult = A++

        return A;
    }

    /*
        Overloading unary operator. 
        Result will be assign to this struct.
    */
    func void operator++()
    {
        // do stuff... this++
    }
}


/*
    We can overload all operators.


    Builtin methods(like operator overloading for struct and enum):
        func [type] first(); // get first element for iteration
        func [type] next([type] current); // get next element for iteration
        func [type] end(); // get last element for stop iteration
*/