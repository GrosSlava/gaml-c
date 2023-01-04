// This examples show features of standard types




func main
{
	// void - can't be as function argument or variable type. Only for function return.

	var bool g;     // 8-bit logic type

	var uint8 a;    // 8-bit unsigned integer [0 - 255]
	var uint16 b;   // 16-bit unsigned integer [0 - 65 535]
	var uint32 c;   // 32-bit unsigned integer [0 - 4 294 967 295]
	var uint64 d;   // 64-bit unsigned integer [0 - 18 446 744 073 709 551 615]
	var int8 a2;    // 8-bit  integer [-128 - 127]
	var int16 b2;   // 16-bit integer [-32 768 - 32 767]
	var int32 c2;   // 32-bit integer [-2 147 483 648 - 2 147 483 647]
	var int64 d2;   // 64-bit integer [-9 223 372 036 854 775 808 - 9 223 372 036 854 775 807]

	var addr_t e;   // with system pointer size
	var float f;    // 32-bit floating number
	var double f2;  // 64-bit floating number

	/* 
		Make sure that all numeric types depends on system architecture. 
		So, if your system(e.g 32 bit machine) not support 64-bit types they will cause compile error.
	*/

	var char h;     // 32-bit symbol type(utf-16)
	var string s;   // builtin type for easy operations with strings, see documentation about string

	var vector4d v4; // builtin type for easy operations with 4d-vectors, see documentation about vectors
	var vector3d v3; // builtin type for easy operations with 3d-vectors, see documentation about vectors
	var vector2d v2; // builtin type for easy operations with 2d-vectors, see documentation about vectors

	var array<|uint8|> arr; // builtin array for any type, see documentation about arrays
	//var class<|class_type|> // container of any class type
}