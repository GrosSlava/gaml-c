# GAML (Game programming language)

**GAML** - it is c-style based programming language which designed mostly for game development. \
**GAML-c** - first compiler for GAML.



## Requirements

On Linux: gcc, g++, PyProjectBuilder, llvm \
On Windows: Visual Studio 2017 or higher, native tools command prompt for VS, llvm

## How to build compiler

On Linux: install [`PyProjectBuilder`](https://github.com/GrosSlava/PyProjectBuilder) and use this tool to make gaml-c \
On Windows: use Visual Studio 2017 or higher

## Set syntax highlighting

For Windows: \
put folder *TextHeighlight\VSCode\extensions\gaml* into *Microsoft VS Code\resources\app\extensions* 

For Linux: \
put folder *TextHeighlight\VSCode\extensions\gaml* into *.var/app/com.visualstudio.code/data/vscode/extensions/*

## Guides

To have base guide see examples in *Documentation\Examples*. \
**The language documentation and standard is under development.**



## Compiler options

```-h```, ```--help```                  help information \
```-v```, ```--version```               compiler version \
```-p```, ```--package=PATH```          add package dir with gaml files to compiling \
```-b PATH```                           static link package dir with object files \
```-l PATH```, ```--lib=PATH```         link library \
```-o PATH```, ```--output=PATH```      output directory \
```--name=NAME```                       set compiled program name \
```-O NUMBER```                         set optimization level [0 - 2] \
```-W NUMBER```                         set warning level [0 - 3] \
```--code_type=TYPE```                  set code generation type (ReduceC, LLVM) \
```--subsystem=TYPE```                  set type of subsystem (Console, Window) \
```--platform=TYPE```                   set target platform (Undefined, Windows, Linux) \
```--arch=ARCH```                       set target arch (x86, x86_64, ARM, ARM_64) \
```-e NAME```, ```--entry=NAME```       set entry point name \
```-L PATH```, ```--libpath=PATH```     add libs searching dir \
```--debug```                           include debug information \
```--DLL```                             output result will be in dll \
```--w2e```                             convert warnings to errors \
```--no_builtin```                      no builtin content \
```--freestanding```                    generate freestanding code \
```--no_stack_protector```              disable stack protection \
```--no_red_zone```                     disable red zones \
```--no_translate```                    do not translate the generated code \
```--dump_lexeme```                     dump lexemes to file \
```--dump_modules```                    dump modules dependencies to file \
```--dump_c```                          dump generated code to file \
```-S```, ```--dump_asm```              dump assembler to file \
```-c```                                no linking, only compile \
```-q```, ```--quiet```                 no compiler messages \
```--no_context```                      no context string with errors \
```--progress```                        show compilation progress
