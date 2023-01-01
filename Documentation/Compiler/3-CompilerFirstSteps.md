# How to use gaml-c

gaml-c works from your system terminal(console). \
In Windows we recommend to use *Command Prompt for VS*

To run gaml-c use executable file with options. \
Options can be short(-[option short name]) or long(--[option long name]).

To list all options use: -h or --help

To pass a value with a short option, put your argument after the option without a space. \
To pass a value with a long option, put your argument after the option with '='.

gaml-c input files extensions:
- .gaml (gaml source file)
- .o (object file on linux)
- .obj (object file on windows)

All arguments without the specified option ('-' or '--') are interpreted as an input file.
