
import MyModule1 as M; // import our module with alias, alias is visible only in this file
import MyPackage.SubPackage as P; // import all from package folder
import MyPackage.MyModule2; // import selected module from package




***
	// Program entry point.
***
func main
{
	// call our module functions
	M::foo();
	MyModule1::foo2();

	MyPackage.MyModule2::foo(); // function with same name from package module

	MyPackage.SubPackage.MyModule3::foo(); // all modules from the package have been imported
	P.MyModule3::foo(); // use package alias

	// use declared in module type alias
	var M::MyUnsignedType LVariable = 7;
}
