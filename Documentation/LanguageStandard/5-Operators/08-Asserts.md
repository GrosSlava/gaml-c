# Asserts

Asserts are control statements that provide code validation during execution or compilation. \
Each assert will generate exception (runtime or compile) if given expression is `false`.

### Example

```
// Runtime time assert
assert(1 == 1);
```

```
// Runtime time assert
assert(1 == 2); // generate error
```

```
// Runtime time assert
assert(1 == 2, "Smth went wrong"); // generate error with mesage
```

```
// Compile time assert
static_assert(1 == 1);
```

```
// Compile time assert
static_assert(1 == 2); // generate error
```

```
// Compile time assert
static_assert(1 == 2, "Smth went wrong"); // generate error with mesage during compilation
```



## Compile time error/warning generators

**GAML** provides compile-time error/warning generation.

### Example

```
// generate compile-time error with message
static_error("My message");
```

```
// generate compile-time warning with message
static_warning("My message");
```

```
// log message during compilation
static_message("My message");
```
