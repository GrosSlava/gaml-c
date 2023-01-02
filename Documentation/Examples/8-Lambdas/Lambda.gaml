// This examples show features of lambdas declaration




/*
    Define new type as lambda.
*/
using MyLambdaSignature = lambda (int32, int32) => int32;

// lambda formula: lamda (input arguments types) => return type


***
    /*
        Use lambda as function argument.
        Function can take and return only lamdas, no functions, unlike C.
    */

    @param InL: const MyLambdaSignature
***
func foo
{
    InL(5, 4);
}



***
    // This monster takes lambda as argument and return lambda as taken lambda result.

    @param InL: lambda (int32, int32) => lambda (bool, int32) => void
    @return Result: lambda (bool, int32) => void
***
func bar
{
    return InL(5, 4)
}

/*
    Better variant.
*/
using LambdaOut = lambda (bool, int32) => void;
using LambdaIn = lambda (int32, int32) => LambdaOut;

***
    @param InL: LambdaIn
    @return Result: LambdaOut
***
func Goodbar
{
    return InL(5, 4)
}




func main
{
    var int32 LVar = 99;

    /*
        We can declare local lambda.
        NOTE: Lambdas can be declared only inside function.
    */
    var MyLambdaSignature LLambda = lambda (int32 A, int32 B) => int32 
    [LVar] // context (enumerate context or use 'this' for class)
    {
        return A + B + LVar;
    }

    // call lambda
    LLambda(5, 6);

    // pass lambda into function
    foo(LLambda);

    // create anonimus lambda and pass it into function
    // NOTE: We can create lambda without context
    foo(lambda (int32 A, int32 B) => int32 { return A * B })
}
