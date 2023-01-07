# Class reflection

Reflection provides access to fields and methods by name. \
Reflection works with `struct`, `object`, `component`, `enum`. \
Reflection will not be available if its use is disabled in the compiler settings.



1. Get all public methods names.
```
var array<|string|> Names = [TYPE]::methods;
```

2. Get all public fields names.
```
var array<|string|> Names = [TYPE]::fields;
```

3. Call public method by name. \
If method not exist it will cause runtime error.
```
// for struct
A.call("MethodName");

// for object/component
A->call("MethodName");
```

See [enum](06-Enum.md) reflection \
See [class](../2-Types/10-Class.md) type reflection \
See [operators](../5-Operators/01-Operators.md) reflection
