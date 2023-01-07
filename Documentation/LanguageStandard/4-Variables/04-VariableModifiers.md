# Variable modifiers



> `const` \
> Set variable as const. \
> So it can't be changed and should contain default value.
> `const` variable with [`class`](../6-Classes/01-ClassSystem.md) type can only provide access to const methods.
> `const` variable can be asigned only to `const` variable.

> `static` \
> Set variable as static. \
> `static` variables are visible only inside function body, but created only once.
> `static` variable inside [`class`](../6-Classes/01-ClassSystem.md) technically is global variable.

### Example

```
var static const uint8 StaticInt = 7;
```
