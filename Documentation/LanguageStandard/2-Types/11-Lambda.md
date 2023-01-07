# Lambda

Lambda - it is anonim function with context. 



## Lambda features

1. Lambda can be declared as type in **module**, **class**, **function** scope
2. Lambda can be declared and stored in variable in **function** scope
3. Lambda can be created as RValue and passed into function in **function** scope
4. Common function can be used as lambda without context
5. Lambda can't have compile-time code
6. Lambda can return maximum 1 value



## Lambda declaration formula

```
lambda ([1-INPUTS]) => [2-RETURN_TYPE]
[[3-CONTEXT CAPTURE]]
{
	[4-CODE]
}
```
1. Arguments separated by ',' in the order they are passing to lambda (optional)
2. [Type](01-Types.md) of lambda result (optional)
3. List of variables to capture in context for using in lambda (optional)
4. Lambda code

### Example

```
// Create new type. Lambda arguments may not have names.
using MyLambdaSignature = lambda (int32, int32) => int32; 

// Create new type. Lambda arguments may not exist.
using MyLambdaSignature2 = lambda () => int32; 

// Create new type. Lambda return may not exist.
using MyLambdaSignature3 = lambda (); 

// Lambda returning lambda.
using MyLambdaSignature2 = lambda (int32, int32) => lambda (bool, int32);
```

```
var int32 LVar = 99;

// NOTE: Lambdas with realization can be declared only inside function.
var MyLambdaSignature LLambda = lambda (int32 A, int32 B) => int32 
[LVar] // context (enumerate context or use 'this' for class)
{
	return A + B + LVar;
};

// call lambda
LLambda(5, 6);

// pass lambda into function
foo(LLambda);

// Create anonimus lambda and pass it into function.
// NOTE: We can create lambda without context.
foo(lambda (int32 A, int32 B) => int32 { return A * B });

// pass function bar into foo as lambda (compiler will create lambda with empty context)
foo(bar);
```
