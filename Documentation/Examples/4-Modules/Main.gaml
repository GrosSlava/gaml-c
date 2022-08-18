
import MyModule as M; // import our module with alias, alias is visible only in this file



func void main()
{
    // call our module functions
    M::foo();
    MyModule::foo2();

    // use declared in module type alias
    M::MyUnsignedType LVariable = 7;
}