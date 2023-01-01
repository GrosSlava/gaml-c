# ReduceC

**ReduceC** - it is C with minimum functional. \
We generate code only using this functionality. So your compiler should implement at least ReduceC. \
See ISO C standard before.



## Types:

- void(*) 
- unsigned char(*)
- unsigned short int(*)
- unsigned int(*)
- unsigned long long int(*)
- signed char(*)
- signed short int(*)
- signed int(*)
- signed long long int(*)
- float(*)
- double(*)
	
## Keywords:

- const
- extern
- switch, case
- if, else
- for, do while, while
- break, continue, return
- struct
- __cdecl, __stdcall, __fastcall, __thiscall

## Operators:

- math: =, +, -, *, /, %  
- logic: &&, ||, <, >, ==, !
- binary: &, |, ~, ^, <<, >>
- access: ->, *, .

## Functionality:

- We can coomment code by /**/
- We can use forward declaration for structs and functions
- We can declare our types by *struct [Name] {...};*
- We can declare function *[return type][Name] ([arguments...]);*
- We can declare global variable *[Type][Name];*
- We can declare function or global variable as *extern*
- We can implement function
- We can declare and use pointer to function [return type] (*[Name])([arguments...])
- We can get address by *&*
- We can cast variable *(CastType)Variable*
- Your compiler should generate platform specific initialization code (_start)
- Your compiler should support entry point( int main(int argc, char** argv), int wWinMain(...))
- Your compiler should generate functions with the correct name according to the standard.

## For better compatibility:

- Your compiler can generate object file
- Your compiler can generate assembler file
- Your compiler can generate executable file
- Your compiler can generate "dll" file
- Your compiler have optimization option flags
- Your compiler have warning option flags
- Your compiler can put result in selected folder
- Your compiler can set custom entry point
