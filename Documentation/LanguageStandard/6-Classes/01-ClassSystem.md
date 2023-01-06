# Class system

**GAML** provides class ecosystem. \
Each class can be declared only in **module** scope. \
**GAML** doesn't have forward declaration.



## Kinds of class

1. [Structure](02-Strunct.md)
2. [Object](03-Object.md)
3. [Interface](04-Interface.md)
4. [Component](05-Component.md)
5. [Enumeration](06-Enum.md)



## Class memory management

Different classes behave differently when managing memory. \
Some of them are always on the stack (sometimes can be optimized by compiler with using pointer). \
Some of them are always in the heap (managed by the garbage collector).

1. `Static` variables are constructed before user code start and remove from memory after program end
2. [Standard types](../2-Types/02-StandardTypes.md), [Structure](02-Strunct.md), [Enumeration](06-Enum.md) are always on the stack and delete from memory when the variable goes out of scope
3. [Interface](04-Interface.md), [Object](03-Object.md), [Component](05-Component.md) are always in the heap and delete from memory by the garbage collector when there are no references to this memory



## Class access modifiers

- `public` - set class to be visible anywhere
- `protected` - set class to be visible only in current package
- `private` - set class to be visible only in current module



## Class members access modifiers

- `public` - set member to be visible anywhere
- `protected` - set member to be visible only in this class and its children
- `private` - set member to be visible only in this class



## Class inheritance

When some class A inherit other one B:
- A starts to contains all B data
- A provides polymorphic behaviour based on B
- A not change inherited data's access modifiers
- A can contains methods with same names as in B
- A can **not** contains fields with same names as in B 