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
            Result will be assign to this struct.
        */

        @param B: const FMyStruct
    ***
    func OpAssign
    {
        // do stuff... this = B
    }

    ***
        /*
            Overloading binary operator. 
            Result will be new copy of struct.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: FMyStruct
    ***
    func OpPlus
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
    func OpPlus
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
    func OpIncrement
    {
        // do stuff... Result = A++
    }
    ***
        /*
            Overloading unary operator. 
            Result will be assign to this struct.
        */
    ***
    func OpIncrement
    {
        // do stuff... this++
    }

    ***
        /*
            Overloading binary operator. 
            Result will be new copy of struct.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: FMyStruct
    ***
    func OpMinus
    {
        // do stuff... Result = A - B
    }
    ***
        /*
            Overloading binary operator. 
            Result will be assign to this struct.
        */

        @param B: const FMyStruct
    ***
    func OpMinus
    {
        // do stuff... this - B
    }

    ***
        /*
            Overloading unary operator. 
            Result will be new copy of struct.
        */
        @param A: const FMyStruct
        @return Result: FMyStruct
    ***
    func OpDecrement
    {
        // do stuff... Result = A--
    }
    ***
        /*
            Overloading unary operator. 
            Result will be assign to this struct.
        */
    ***
    func OpDecrement
    {
        // do stuff... this--
    }

    ***
        /*
            Overloading binary operator. 
            Result will be new copy of struct.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: FMyStruct
    ***
    func OpMultiply
    {
        // do stuff... Result = A & B
    }
    ***
        /*
            Overloading binary operator. 
            Result will be assign to this struct.
        */

        @param B: const FMyStruct
    ***
    func OpMultiply
    {
        // do stuff... this * B
    }

    ***
        /*
            Overloading binary operator. 
            Result will be new copy of struct.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: FMyStruct
    ***
    func OpDivide
    {
        // do stuff... Result = A / B
    }
    ***
        /*
            Overloading binary operator. 
            Result will be assign to this struct.
        */

        @param B: const FMyStruct
    ***
    func OpDivide
    {
        // do stuff... this / B
    }

    ***
        /*
            Overloading binary operator. 
            Result will be new copy of struct.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: FMyStruct
    ***
    func OpModdiv
    {
        // do stuff... Result = A % B
    }
    ***
        /*
            Overloading binary operator. 
            Result will be assign to this struct.
        */

        @param B: const FMyStruct
    ***
    func OpModdiv
    {
        // do stuff... this % B
    }

    ***
        /*
            Overloading binary operator. 
            Result will be new copy of struct.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: FMyStruct
    ***
    func OpPower
    {
        // do stuff... Result = A ^^ B
    }
    ***
        /*
            Overloading binary operator. 
            Result will be assign to this struct.
        */

        @param B: const FMyStruct
    ***
    func OpPower
    {
        // do stuff... this ^^ B
    }

    ***
        /*
            Overloading unary operator. 
            Result will be new copy of struct.
        */

        @param A: const FMyStruct
        @return Result: FMyStruct
    ***
    func OpNegate
    {
        // do stuff... Result = -A
    }
    ***
        /*
            Overloading unary operator. 
            Result will be assign to this struct.
        */
    ***
    func OpNegate
    {
        // do stuff... this = -this
    }

    ***
        /*
            Overloading binary operator. 
            Result should be bool.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: bool
    ***
    func OpLess
    {
        // do stuff... Result = A < B
    }
    ***
        /*
            Overloading binary operator. 
            Result should be bool.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: bool
    ***
    func OpLessEqual
    {
        // do stuff... Result = A <= B
    }
    ***
        /*
            Overloading binary operator. 
            Result should be bool.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: bool
    ***
    func OpGreater
    {
        // do stuff... Result = A > B
    }
    ***
        /*
            Overloading binary operator. 
            Result should be bool.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: bool
    ***
    func OpGreaterEqual
    {
        // do stuff... Result = A >= B
    }
    ***
        /*
            Overloading binary operator. 
            Result should be bool.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: bool
    ***
    func OpEqual
    {
        // do stuff... Result = A == B
    }
    ***
        /*
            Overloading binary operator. 
            Result should be bool.
        */

        @param A: const FMyStruct
        @param B: const FMyStruct
        @return Result: bool
    ***
    func OpNotEqual
    {
        // do stuff... Result = A != B
    }

    ***
        /*
            Overloading unary operator. 
            Result can be any type to convert.
        */

        @return Result: bool
    ***
    func OpToType
    {
        // do stuff... Result = convert A to bool
    }


    // Other operators
/*
    ***
        // Get first element for iteration
        @return Result: [type]
    ***
    func First {}
    ***
        // Get next element for iteration
        @return Result: [type]
    ***
    func Next {}
    ***
        // Get last element for stop iteration
        @return Result: [type]
    ***
    func End {}

    ***
        // Access to internal elemants by [].
        @param Index: int32
        @return Result: [type]
    ***
    func OpElementAccess {}
*/
}

