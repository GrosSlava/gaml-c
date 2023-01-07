# Standard types

Standard types are types that are elementary representations of data of different bit lengths. \
All numeric types depends on system architecture. \
So, if your system (for example, a 32-bit machine) does not support 64-bit types, using them will cause a compilation error.



`uint8` - 8-bit unsigned integer [0 - 255] \
`uint16` - 16-bit unsigned integer [0 - 65 535] \
`uint32`- 32-bit unsigned integer [0 - 4 294 967 295] \
`int64`- 64-bit unsigned integer [0 - 18 446 744 073 709 551 615] \
`int8` - 8-bit  integer [-128 - 127] \
`int16` - 16-bit integer [-32 768 - 32 767] \
`int32` - 32-bit integer [-2 147 483 648 - 2 147 483 647] \
`int64` - 64-bit integer [-9 223 372 036 854 775 808 - 9 223 372 036 854 775 807]

`bool`- 8-bit logic type (true/false; 0 = false; other numbers = true) \
`addr_t` - unsigned int with system pointer size \
`float` - 32-bit floating number \
`double` - 64-bit floating number
