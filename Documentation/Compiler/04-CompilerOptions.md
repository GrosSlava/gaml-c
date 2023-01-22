# Compiler options

> `-h`, `--help` \
> Show help information and stop

> `-v`, `--version` \
> Show compiler version and stop

> `-p`, `--package=PATH` \
> Add package dir with gaml files to compiling (subfolders are included)

> `-b PATH` \
> Static link package dir with object files (subfolders are included)

> `-l PATH`, `--lib=PATH` \
> Link library

> `-o PATH`, `--output=PATH` \
> Set output directory (only folder for result)

> `--name=NAME` \
> Set result name

> `-O NUMBER` \
> Set optimization level [0 - 2] (0 - no optimization, 1 - size optimization, 2 - speed optimization)

> `-W NUMBER` \
> Set warning level [0 - 3] (0 - no warnings, 1 - minor warnings, 2 - common warnings, 3 - serious warnings)

> `--code_type=TYPE` \
> Set code generation type (ReduceC, LLVM)

> `--subsystem=TYPE` \
> Set type of subsystem (Console, Window)

> `--platform=TYPE` \
> Set target platform (Undefined, Windows, Linux)

> `--arch=ARCH` \
> Set target arch (x86, x86_64, ARM, ARM_64)

> `-e NAME`, `--entry=NAME` \
> Set entry point name

> `-L PATH`, `--libpath=PATH` \
> Add libs searching dir    

> `--debug` \
> Include debug information and mark as debug build

> `--DLL` \
> Output result will be in dll

> `--w2e` \
> Convert all warnings to errors 

> `--no_builtin` \
> No builtin content

> `--no_reflection` \
> Disable reflection code generation

> `--freestanding` \
> Generate freestanding code

> `--no_stack_protector` \
> Disable stack protection

> `--no_red_zone` \
> Disable red zones

> `--no_translate` \
> Do not translate the generated code

> `--dump_lexeme` \
> Dump lexemes to file

> `--dump_ast` \
> Dump all ast to file

> `--dump_modules` \
> Dump modules dependencies to file

> `--dump_ir` \
> Dump IR to file

> `--dump_c` \
> Dump generated code to file

> `-S`, `--dump_asm` \
> Dump assembler to file

> `-c` \
> No linking, only compile

> `-q`, `--quiet` \
> No compiler messages

> `--no_context` \
> No context string with errors

> `--progress` \
> Show compilation progress

> `-t`, `--time` \
> Show total compilation time


                
## Example options line:

1. ./gaml-c Test/MyTestFile.gaml // compile file and create executable
2. ./gaml-c -c Test/MyTestFile.gaml // compile, but not create executable
3. ./gaml-c -c --progress -pTest // compile to object files all gaml files from folder "Test" and show compilation progress
4. ./gaml-c -O2 --package=Test --name=ProgramName // compile all gaml files from folder "Test" with optimization level 2 and set exceutable file name "ProgramName"
