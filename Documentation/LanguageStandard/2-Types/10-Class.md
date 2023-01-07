# class

TODO



object UMyObject
{

}

object UMyObject2(UMyObject)
{

}



func main
{
	var class<|UMyObject|> LClass;          // by default here will be None
	LClass = UMyObject2::StaticClass();     // set local class container with UMyObject2 class

	var UMyObject LObject = CreateObject<|UMyObject|>(LClass);  // instantiate object by class type
	// CreateComponent<|UMyComponent|>(LClass);                 // version for components
}