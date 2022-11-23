// This examples show features of reflection in classes


object UMyObject
{

}

object UMyObject2 : UMyObject
{

}


func main
{
    class<|UMyObject|> LClass; // by default here will be None
    LClass = UMyObject2::StaticClass(); // set local class container with UMyObject2 class

    UMyObject LObject = CreateObject<|UMyObject|>(LClass); // instantiate object by class type
    LObject = CreateObject(UMyObject2::StaticClass()); // alternative version

    // CreateComponent<|UMyComponent|>(LClass); // version for components


    issubclass(LClass, UMyObject); // we can check class type
}