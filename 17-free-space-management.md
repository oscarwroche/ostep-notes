# How should free space be managed when satisfying allocation requests ?

*  Interface considered : malloc / free - free list on the heap
*  Concerns : mainly **external fragmentation**
*  Constraints : **no compaction**, contiguous region of bytes

## Low-level mechanisms

*  **Splitting** is used when requesting space that is smaller than the size of a free chunk space from the free list
*  **Coalescing** is used to merge contiguous free blocks of memory (for example when a block between two free blocks is freed)

### How to track the size of allocated regions ?

When calling `free`, a pointer is given as an argument - how does the library know how much memory has to be freed ?
Usually, allocators track such information using a **header** stored just before the block. It contains a **size** as well as a **magic number** to check integrity.
The header has to be taken into account when allocating memory.

### How to use the free list ?

Structure of a node from the free list :

```c
typedef struct __node_t {
int size;
struct __node_t *next;
} node_t;
```

Initialization :

```c
// mmap() returns a pointer to a chunk of free space
node_t *head = mmap(NULL, 4096, PROT_READ|PROT_WRITE,
MAP_ANON|MAP_PRIVATE, -1, 0);
head->size = 4096 - sizeof(node_t);
head->next = NULL;
```

The **head** pointer moves to the start of the next free region when memory is allocated or when a block is freed (this is possible because the pointer returned by malloc is fed back to free later). The **next** pointer of this new region is set to the previous **head**.

When freeing a block, the list is gone through to see if adjacent free blocks can be coalesced.

### Growing the heap

The heap can eventually run out of space, in which case the UNIX **sbrk** call can be made.

## Strategies

How to find a free block in the most efficient way ?

### Best fit

Take smallest block among blocks that are at least as big as the requested size

### Worst fit

Take largest chunk and take requested amount from it, leave remaining chunk on free list - attempts to leave large chunks free but poor performance.

### First fit

Take first block that is big enough - issue is that the start of the free list get a lot of small items : **address-based ordering** is a solution to this.

### Next fit

Same as first fit but keeping track of when the last lookup was - allows to spread blocks more evenly.

## Other approaches

### Segregated lists

*  Keep some space for popular requests of a given size - the **slab allocator** is a method to balance the space between this space and the general memory.

### Buddy allocation

*  Makes coalescing simpler by allocating blocks by repeatedly dividing memory by two - so that each memory block has another "buddy" of its size that can be used for coalescing if the block is freed (checking buddies of increasing size until another free space is found)

### Issues

Most of the solutions preseted here are not scalable because they rely on a list structure a lot - other structures (trees etc ...) can be more efficient.

