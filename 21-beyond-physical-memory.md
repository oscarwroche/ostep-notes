# How to provide the illusion of a larger virtual address space ?

With the hard drive - one more level in the hierarchy of memory
Necessary for convenience when running processes for it to be transparent (everything seems like it's in memory)

## Swap space

Name of the hard drive memory that the OS can read from and write to - in page-sized bits. The OS neeeds to remember the disk addresses of such pages

Pages for code are also on hard drive and need to be swapped in when running a program.

## The present bit

To the usual look up TLB / make translation mechanism must be added to tell the hardware if the page is in memory or on disk : this is called the **present bit**. Trying to access pages not in memory is a **page fault**

## The page fault

Page fault handlers are generally **software** (reasons : accessing disk is slow so OS overhead is minimal - and hardware doesn't know swap space or I/O etc)

The OS will fetch the page from disk, mark it as present and update the PFN of the page table (and maybe update the TLB cache so that it doesn't fail on the next try) - and then retry.

While servicing I/O, the OS can run other ready processes

## What if memory is full when swapping in ?

This is the **page replacement policy** - crucial so that disk I/O doesn't become a bottleneck

## Page fault control flow

Ask yourself the question of what happens when a program fetches data from memory.

*  Asssuming there is a TLB miss
*  Check if page is **present** and **valid** -> grab page and put in TLB, retry
*  Otherwise run page fault handler :

```
1 PFN = FindFreePhysicalPage()
2 if (PFN == -1) // no free page found
3 PFN = EvictPage() // run replacement algorithm
4 DiskRead(PTE.DiskAddr, PFN) // sleep (waiting for I/O)
5 PTE.present = True // update page table with present
6 PTE.PFN = PFN // bit and translation (PFN)
7 RetryInstruction() // retry instruction
```

## When to replace ?

The system uses **watermarks** to define levels past which page swapping has to be operated. A **swap / page daemon** is used in the background to evict pages accordingly.

Pages can be **clustered** or **grouped** to reduce the overhead associated with disk operations.

