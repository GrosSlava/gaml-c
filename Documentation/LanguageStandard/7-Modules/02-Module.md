# Module

Module it is unit of code.



## Module features

1. Each file (except main file) must start with module declaration
2. Module provides namespace with the name as the module
3. Module provides custom access to all module members
4. Module can import other modules
5. Imported module is not imported twice
6. Access to module content provides by '::' operator
7. Module can be separated to "header" and "source" files
8. By default all module members (classes, functions, aliases ...) are public
9. By default module itself is public



## Main module

1. Main module must be named "main" or can not declare module (generated automatically)
2. All unnamed modules interpreted as main
3. Main module can't be imported
4. [Entry point](../8-Main/01-Main.md) will be searched in main module



## Module declaration formula

```
***
	[1-MODIFIERS]
***
[2-ACCESS_MODIFIER] module [3-MODULE_NAME]; 
```
1. [MODIFIERS](04-ModuleModifiers.md) are a list of keywords to give a module a special behaviour (can be empty or not exist)
2. ACCESS_MODIFIER is keyword to set module visibility (optional)
3. MODULE_NAME is identifier which can contains only english alphabet letters, '_' and digits after first letter

### Module access modifiers

- `public` - set module to be visible anywhere
- `protected` - set module to be visible only in current package
- `private` - set module to be visible only in current subpackage

### Module name

- Module name should match file name
- Module name must contain relative path from the root of package, separated by '.'

### Example

```
// folder structure:
/Project
	/MyPackage
		/MyModule2.gaml
		/SubPackage
			/MyModule3.gaml
			/MyModule4.gaml
	/Main.gaml
	/MyModule1.gaml


// file MyModule1.gaml
***
	@deprecated
***
module MyModule1;

// file MyModule2.gaml
module MyPackage.MyModule2;

// file MyModule3.gaml
module MyPackage.SubPackage.MyModule3;

// file MyModule4.gaml
module MyPackage.SubPackage.MyModule4;

// file Main.gaml
module main
```



See [module import](05-ModuleImport.md) \
See [module separation](06-ModuleSeparation.md)
