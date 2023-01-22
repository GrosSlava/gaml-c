# Class modifiers

All modifiers must be listed in description block `*** .... ***` \
All class modifiers must start with '@'. \
Modifiers are not inherited.



> `@deprecated` \
> Mark class as deprecated. \
> When user try to use it in the code, it will cause a warning. \
> Can be used once. \
> Order is not important.

> `@unimplemented` \
> Mark class as unimplemented. \
> This class can't have any realization (field or method) and can't be used in code. \
> This class not appear in generated code. \
> Can be used once. \
> Order is not important.

> `@static` \
> Mark class as static. \
> This class can be instantiated only once. \
> Each new instance will be pointing to one copy. \
> Can be used once. \
> Order is not important.

```
// Singleton example like in c++.

***
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
		return UMySingletonObject();
	}
}
```

> `@final` \
> Mark class as final. \
> This class can't be inhereted. \
> Can be used once. \
> Order is not important.
