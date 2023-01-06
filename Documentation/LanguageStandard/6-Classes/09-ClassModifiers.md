
***
	/*
		static modifiers marks that this object can be instantiated only once,
		each new instance will be pointing to one object

		static modifier works only with object
	*/
	@static
***
object UMyStaticObject
{

}

***
	/*
		same to UMyStaticObject, but you need to call UMySingletonObject::Get() method to get instance
	*/
	@static
***
object UMySingletonObject
{
	private func UMySingletonObject {}

	***
		@static

		@return Result: UMySingletonObject
	***
	public func Get
	{
		var static UMySingletonObject = UMySingletonObject();
		return UMySingletonObject;
	}
}