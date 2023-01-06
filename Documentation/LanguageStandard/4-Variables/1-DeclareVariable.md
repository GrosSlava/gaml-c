# Declare variable

Variables can be declared only inside function body(compile-time/runtime).



## Variable declaration formula

```
var [1-MODIFIERS] [2-TYPE] [3-NAME];
```
1. MODIFIERS: `const`, `static`
2. TYPE - any [type](../2-Types/1-Types.md)
3. Variable name is unique identifier which can contains only english alphabet letters, '_' and digits after first letter

### Example

```
var uint8 A;
```
By default variable contains trash.



## Give default value

```
var [1-MODIFIERS] [2-TYPE] [3-NAME] = [4-EXPRESSION];
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

> `static` \
> Set variable as static. \
> Static variables are visible only inside function body, but created only once.

### Example

```
var static const uint8 StaticInt = 7;
```
