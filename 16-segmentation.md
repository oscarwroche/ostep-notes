# How to support a large address space ? How to handle the free space between the stack and the heap

## Generalized Base and Bounds

The idea is to have one base / bounds pair for each logical segment (code / heap / stack). This allows to place segments independently in memory.

Example :

| Segment | Base | Size |
--------------------------
| Code | 32K | 2K |
| Heap | 34K | 3K |
| Stack | 28K | 2K |

When using the virtual address, the **offset** of the segment must be subtracted from the address before being added to the segment base.

Referring to an illegal address is called a **segmentation fault** (even when the system doesn't support segmentation ...).

## Which segment is being referred to ?

**Explicit approach** : have a 14 bit address : 2 bits for segment and 12 bits for offset.

Only 1 top bit can be used if the code is in the same place as the heap (having 2 bits can limit the total address space for a given segment).

**Implicit approach**  : determine the segment by seeing how the address is formed (from the program counter / stack pointer / etc ...)

## Specificities of the stack 

The stack grows backwards. So the address `11 1100 0000 0000` (stack segment + 3kb) must be read as (stack base - (max. segment size) + 3kb) = 28kb - 4kb + 3kb = 27kb

## Sharing

Sharing some address spaces (e.g. code sharing) can be efficient. To regulate sharing, **protection bits** are added to define permissions for each segment.

## Segmentation granularity

Granularity ~ number of segments : coarse-grained ~ code + stack + heap
Some earlier machines had way more segments in order to optimize memory use

## OS support

*  On context switches, the segment registers are saved and restored.
*  The OS may have to grow the heap before allocating memory via malloc.
*  How to find free space ? Problem of small holes in memory aka **external fragmentation**. Problems when the requested amount of memory doesn't exist contiguously in memory. A solution to this is called **compacting** memory, i.e. periodically rearranging memory to create the desired contiguous spaces. This strategy is however expensive. Another solution is finding clever algorithms when choosing where to allocate memory.
