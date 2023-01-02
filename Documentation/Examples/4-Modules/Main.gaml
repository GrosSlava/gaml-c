
import MyModule as M; // import our module with alias, alias is visible only in this file
import MyPackage.SubPackage; // import all from package folder
import MyPackage.MyModule2; // import selected module from package




***
    // Program entry point.
***
func main
{
    // call our module functions
    M::foo();
    MyModule::foo2();

    // use declared in module type alias
    var M::MyUnsignedType LVariable = 7;
}
