// This examples show features of operators overloading


/*
    Only enum, struct can have overloaded operators.
    See example with struct.
*/


struct FMyStruct 
{
    ***
        /*
            Overloading binary operator. 
            Result will be new copy of struct.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: FMyStruct
    ***
    func operator+
    {
        // do stuff... Result = A + B
    }

    ***
        /*
            Overloading binary operator. 
            Result will be assign to this struct.
        */

        @param B: const FMyStruct
    ***
    func operator+
    {
        // do stuff... this + B
    }

    ***
        /*
            Overloading unary operator. 
            Result will be new copy of struct.
        */
        @param A: const FMyStruct
        @return Result: FMyStruct
    ***
    func operator++
    {
        // do stuff... Result = A++
    }

    ***
        /*
            Overloading unary operator. 
            Result will be assign to this struct.
        */
    ***
    func operator++
    {
        // do stuff... this++
    }
}


/*
    We can overload all operators.


    Builtin methods(like operator overloading for struct and enum):

        ***
            // get first element for iteration
            @return Result: [type]
        ***
        func first; 

        ***
            // get next element for iteration
            @return Result: [type]
        ***
        func next; 

        ***
            // get last element for stop iteration
            @return Result: [type]
        ***
        func end; 
*/