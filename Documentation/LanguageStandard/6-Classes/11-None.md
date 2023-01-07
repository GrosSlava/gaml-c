# None

None - it is keyword that refers to global `static const object` which means "no data".



## None featues

- None can't be changed
- None can be assign only to [interface](04-Interface.md), [object](03-Object.md), [component](05-Component.md)
- None doesn't have any fields or methods
- Using operator `->` with None cause runtime error
- None can't be inhereted
- None can't be garbaged



## None with reflection operators

- None::methods == []
- None::fields == []
- None::StaticClass() == None
- CreateObject<|T|>(None) // error
- None->call("Method") // error
- operators `is` and `==` for checking equality for None are same
- sizeof(None) == 0
- typeof(None) == None
- nameof(None) == "None"
- alignof(None) == 0
- isfunction(None) == false
- isenum(None) == false
- isenum(None) == false
- isinterface(None) == false
- isobject(None) == true
- iscomponent(None) == false
- issubclass(a, None) == false
- isinstance(None, None) == false
- isinstance(a, None) == false
- isiterable(None) == false
- isenumerable(None) == false
- isabstract(None) == false
- isalias(None, None) == false
- islambda(None) == false
- isobject(None) == true
- addr(None) == 0
- default(None) == None 
