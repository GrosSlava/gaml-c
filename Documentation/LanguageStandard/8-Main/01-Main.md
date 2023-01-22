# Main

**GAML** like in C/C++ must have entry point.

**NOTE**: entry point can be declared only in [main module](../7-Modules/02-Module.md)



## Entry point features

1. Entry point function can be changed by user in compiler settings
2. Entry point function can have different signature (see below)
3. Entry point it is part of program [start pipeline](02-ProgramStartPipeline.md)
4. Selection of function signature depends on program [subsystem](../1-GAML/05-BuildSubsystems.md)



## Default entry point signatures

1. Minimal signature \
Works on any subsystem
```
func main
{

}
```

2. Signature with return success code \
Works on any subsystem
```
***
	@return Result: int32
***
func main
{
	return 0;
}
```

3. Signature only for `console` subsystem
```
***
	@param Args: const array<|string|>
	@return Result: int32
***
func main
{
	return 0;
}
```

4. Signature only for `window` subsystem
```
***
	@return Result: int32
***
func WinMain
{
	return 0;
}
```

5. Signature only for `dynamic library`
```
***
	@return Result: int32
***
func DllMain
{
	return 0;
}
```



## Additional module entry points

Each module (not only main) can override next functions:

1. Called at the begin of program, before main \
For dll it called at first load
```
func InitModule
{

}
```

2. Called at the end of program \
For dll it called when unload
```
func DeinitModule
{

}
```



## Reserved and non-overridable functions

The following functions cannot be overridden, otherwise an error will occur:

1. `func InitModuleInternal {}`
2. `func DeinitModuleInternal {}`
