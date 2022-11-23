// This examples show features of template code declaration


/*
    Template are compile-time generated code.
*/


/*
    It is template generator.
*/
template<|Name|> TFooGen
{
    ***
        @return Result: uint8
    ***
    func $Name$ { return 5; }
}

/*
    ***
        @return Result: uint8
    ***
    func $foo$ { return 5; }
*/
TFooGen<|foo|>;



/*
    Each mention of this template will be converted into string "Hello World".
*/
template<||> MY_TEMPLATE_STRING
{
    "Hello World"
}

/*
    Each mention of this template will be converted into string "Hello World" + Arg1.
*/
template<|Arg1|> MY_TEMPLATE_STRING_2
[
    // static code can be here
    if( typeof(Arg1) != string || Arg1 == string ) { static_error("Arg1 should be string"); }
]
{
    "Hello World"$Arg1$
}

/*
    Create template specialization.
    Technically it is new template.
*/
template<|"BABA"|> MY_TEMPLATE_STRING_2
{
    "Hello World dear BABA"
}

template<|int32|> MY_TEMPLATE_STRING_2
{
    "Hello World int32"
}



/*
    Mention of this template will be converted into code.
*/
template<|A|> TMyInlineCode
{
    $A$ *= 6;
    if( $A$ < 22 ) { $A$ += 30; }
}
/*
    Templates can have variadic count of arguments.
*/
template<|...|> TMyVariadicCode
[
    for( int32 i = 0; i < (...).count(); i++ )
    {
        if( typeof($(...)[i]$) != int32 || $(...)[i]$ == int32 )
        {
            static_error("Arg{0} should be int32", i);
        }
    }
]
{
    static for( int32 i = 0; i < (...).count(); i++ )
    {
        $(...)[i]$
        static if( i + 1 < (...).count() )
        {
            $+$
        }
    }
}




func void main()
{
    string s = MY_TEMPLATE_STRING; // s = "Hello World";
    s = MY_TEMPLATE_STRING2<|"!!!"|>; // s = "Hello World!!!";
    s = MY_TEMPLATE_STRING_2<|"BABA"|>; // s = "Hello World dear BABA";
    s = MY_TEMPLATE_STRING_2<|int32|>; // s = "Hello World int32;

    int32 MyInt = 5;
    TMyInlineCode<|MyInt|>; // MyInt *= 6; if(MyInt < 22) { MyInt += 30; };
    MyInt = TMyVariadicCode<|5, 4, MyInt|>; // MyInt = 5 + 4 + MyInt;
}


