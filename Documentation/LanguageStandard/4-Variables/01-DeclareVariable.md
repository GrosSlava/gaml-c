# Declare variable

- Variables can be declared inside function body (compile-time/runtime)
- Variables can be declared inside class body (named field)



## Variable declaration formula

```
var [1-ACCESS_MODIFIER] [2-MODIFIERS] [3-TYPE] [4-NAME];
```
1. ACCESS_MODIFIER can be used only inside class body (optional)
2. MODIFIERS: `const`, `static`
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



## Variable modifiers

> `const` \
> Set variable as const. \
> So it can't be changed and should contain default value.
> `const` variable with [`class`](../6-Classes/01-ClassSystem.md) type can only provide access to const methods

> `static` \
> Set variable as static. \
> `static` variables are visible only inside function body, but created only once.
> `static` variable inside [`class`](../6-Classes/01-ClassSystem.md) technically is global variable

### Example

```
var static const uint8 StaticInt = 7;
```
