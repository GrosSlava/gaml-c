// This examples show features of template classes declaration


/*
    Template classes as templates has number of template arguments.
    But template arguments can contain only types.
    Unlike template code, template classes will be converted to class declaration after first mention in code. 
*/
struct<|typename T|> TMyStruct
[
    // static code can be here
]
{
    T a; // template member with type T
    T b = 5; // if type T can't assign int32, there will be error
}

/*
    It is template struct specialization.
    Technically it is new template.
*/
struct<|int32|> TMyStruct
{
    int32 AA = 99;
}




func main
{
    TMyStruct<|uint8|> LStruct; // TMyStruct with specialization uint8 will be declared in this module
    TMyStruct<|int32|> LStruct2; // this specialization already exists
}