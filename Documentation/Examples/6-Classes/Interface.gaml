// This examples show features of interface declaration




/*
	Declare interface.
*/
interface IMyInterface // interface can be inhereted only from interface(many)
{
	// we can't declare members in interface

	***
		// in interface we can declare only abstract methods, which will be overridden in object or component
		@abstract
	***
	func foo;

	// by default we are in the public block
	// in interface we can use only public and protected modifiers

	// interface can't have constructors
}// not need ';' unlike C


func main
{
	var IMyInterface A; // create local uninitialized variable which can contains any IMyInterface child object
	// A = IMyInterface(); // we can't get instance of interface
}