# Module separtion

Module can be separated to 2 parts: "header" and "source".



## Header

- Header file has ".gh" extension
- Header file must [declare module](02-Module.md)
- Header file can't be compiler
- Header file can be imported



## Source file

- Source file has ".gaml" extension
- Source file must implemet module
- Source file can be compiler
- Source file can't be imported (header file will be selected first)



## Module implementation

".gaml" file can implement module. \
Technically, module implementation it is importing header and add something to it (e.g function implementation).

- Implementation file must start with declaration about implementation
- Implementation file can't be imported
- Name of the implementation file must match the name of the "header" file
- Implementation file can be located anywhere, it not participate in including
- Code in implementation "thinks" that it is in module file with declaration (technically it imports header module and sets it as current)
- Each ".gh" file can have only one ".gaml" implementation file

### Module implementation formula

```
implement [1-MODULE_NAME];
```
1. MODULE_NAME is name ([with path](05-ModuleImport.md)) of module to implement

**NOTE**: All code in module implementation file is visible only for translation and can't be used in other modules, because implementation module can't be imported.
