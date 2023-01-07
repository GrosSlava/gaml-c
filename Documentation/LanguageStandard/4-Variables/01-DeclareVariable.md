# Declare variable

Variable - it is cell for data.



## Variable features

1. Variables can be declared inside function body (compile-time/runtime)
2. Variables can be declared inside class body (named field)
3. Variable has type that can't be changed



## Variable declaration formula

```
var [1-ACCESS_MODIFIER] [2-MODIFIERS] [3-TYPE] [4-NAME];
```
1. ACCESS_MODIFIER can be used only inside class body (optional)
2. [MODIFIERS](04-VariableModifiers.md) are a list of keywords to give a variable a special behaviour (optional)
3. TYPE - any [type](../2-Types/01-Types.md)
4. Variable name is unique identifier which can contains only english alphabet letters, '_' and digits after first letter

### Example

```
var uint8 A;
```
By default variable contains trash.



## Give default value

```
var [VARIABLE] = [EXPRESSION];
```

### Direct set

```
var uint8 A = 5;
```

### Compiler decision to set default value

```
var uint8 A = default(); // A = 0
```

### Reuse default value

```
var uint8 A = 5;
var uint8 B = default(A);
```
