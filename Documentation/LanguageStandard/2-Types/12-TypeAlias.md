# Type alias

Alias can be declared in **module**, **class**, **function** scope.



## Alias features

1. Alias declared in **class**, **function** is visible only in this scope (for **class** in **class** body and it's methods and can't be reached by operator '::')
2. Alias can't be alias for itself
3. Alias can't redefine existed name (variable, field, method, class, module ...)



## Alias declaration formula

```
using [1-ALIAS_NAME] = [2-ORIGINAL_TYPE];
```
1. ALIAS_NAME is unique identifier which can contains only english alphabet letters, '_' and digits after first letter
2. ORIGINAL_TYPE - any [type](01-Types.md)

### Example

```
using MyUnsignedType = uint8;
```
