# What are the interfaces to allocate and manage memory ?

## Types of memory

*  Stack memory : done automatically. For function declarations, arguments, local variables -> only valid during function invocation
*  Heap memory : done manually, long-lived

## malloc

*  Takes a size as argument and returns a pointer to the space or NULL if it fails
*  Size is often `sizeof(x)`
