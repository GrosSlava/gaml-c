# Left/Right hand

Values and objects can be left or right hand operands.

Left hand operand - it is named variable with address in memory. \
Right hand operand - anything that is not left hand.



## Right hand standard types

1. Decimal number - int32
```
var int32 A = 8;
var int32 A = int32(8);
```

2. Hexadecimal number - int32
```
var int32 A = 0x5a;
var int32 B = 0X5A;
var int32 C = int32(0x5a);
```

3. Binary number - int32
```
var int32 A = 11101b;
var int32 B = 11101B;
var int32 C = int32(11101b);
```

4. Real number - double
```
var double A = 8.8;
var double B = 12.e-5;
var double C = 12.1E+5;
var double D = double(8.8);
```

5. Floating number - float
```
var double A = 8.8f;
var double B = 8.8F;
var double C = 12.e-5f;
var double D = double(12.e-5f);
```

6. Char - char
```
var char A = 'a';
var char B = '\n';
var char C = char('\\');
```

7. String - string
```
var string A = "Hello World!\n";
var string C = string("Hello World!\n");
```

8. Boolean - bool
```
var bool A = true;
var bool B = false;
var bool C = bool(1);
```

9. Array - array with type of first element
```
var array<|int32|> A = [1, 2, 3, 4];
```
