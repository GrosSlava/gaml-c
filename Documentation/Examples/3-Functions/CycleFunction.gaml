// This examples show features of cycle function


func int32 foo1()
{
    return 1;
}

func int32 foo2()
{
    return 2;
}

func int32 foo3()
{
    return 3;
}


func int32 CycleFunction()
{
    foo1() ~> foo2() ~> foo3() ~> . // '.' - loop cycle
    // Note: we don't need to have ';' at the end of cycle
}

func int32 CycleFunction2()
{
    foo1() ~> do{ foo2(); foo2(); } 

    foo3();
    foo3();

    foo2() ~> foo3() ~> .
}


func void main()
{
    CycleFunction(); // call foo1()
    CycleFunction(); // call foo2()
    CycleFunction(); // call foo3()
    CycleFunction(); // call foo1()

    CycleFunction2(); // call foo1()
    CycleFunction2(); // call foo2(), foo2()
    CycleFunction2(); // call foo3(), foo3(), foo2()
    CycleFunction2(); // call foo3()
    CycleFunction2(); // call foo2()
    CycleFunction2(); // call foo3()
}
