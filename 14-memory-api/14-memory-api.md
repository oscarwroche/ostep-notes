# What are the interfaces to allocate and manage memory ?

## Types of memory

*  Stack memory : done automatically. For function declarations, arguments, local variables -> only valid during function invocation
*  Heap memory : done manually, long-lived

## malloc

*  Takes a size as argument and returns a pointer to the space or NULL if it fails
*  Size is often `sizeof(x)`
*  Return a pointer to void so programmer can explicitly cast (not needed)

## free

Frees the memory allocated to a variable - the library has to figure out how to free it exactly

## Common mistakes

*  Not allocating memory :

```c
char *src = "hello";
char *dst; // oops! unallocated
strcpy(dst, src); // segfault and die
```

vs.

```c
char *src = "hello";
char *dst = (char *) malloc(strlen(src) + 1);
strcpy(dst, src); // work properly
```

*  Not allocating enough memory (buffer overflow) :

```c
char *src = "hello";
char *dst = (char *) malloc(strlen(src)); // too small!
strcpy(dst, src); // work properly
```

*  Forgetting to Initialize Allocated Memory
*  Forgetting To Free Memory (**memory leak**)
*  Freeing Memory Before You Are Done With It (**dangling pointer**)
*  Freeing Memory Repeatedly (**double free**)
*  **Invalid frees** (with wrong arguments, etc ...)

Tools such as **purify** and **valgrind** used to locate source of memory problems.

## How does the OS support malloc / free ?

Malloc and free are library calls, which themselves use some system calls such as **brk** (changes location of the break i.e. end of the heap) and **sbrk** (similar).

Memory from the system can also be obtained via **mmap** - creates an anonymous memory region called **swap space**.

## Other memory library calls 

*  **calloc** - zeroes memory to prevent errors where allocated memory isn't initialized
*  **realloc** - changes already allocated memory
