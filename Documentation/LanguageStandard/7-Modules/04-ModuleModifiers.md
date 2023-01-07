# Module modifiers

All modifiers must be listed in description block `*** .... ***` \
All module modifiers must start with '@'. \



> `@deprecated` \
> Mark module as deprecated. \
> Importing this module will cause a warning. \
> Can be used once. \
> Order is not important.

> `@unimplemented` \
> Mark module as unimplemented. \
> This module can't be included. \
> Can be used once. \
> Order is not important.

> `@extern_c` \
> Mark module as extern_c. \
> All functions inside this module will be marked as extern_c, this module can't contain classes. \
> Can be used once. \
> Order is not important.
