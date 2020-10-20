# How to reduce the memory taken by page tables ?

The idea is to use other structures than arrays to store them

## Simplest solution : make bigger pages

Problem : like not having pages - internal fragmentation

## Hybrid solution : paging and segments

Instead of having one (very sparse) page table per process, we can have one per segment of each process

The **base** register of each segment points to the *physical address of the page table of this segment*. The top two bits of each virtual address are used to know which segment's page table to access.

This allows to avoid havign a lot of invalid page table entries.

Problems : assumes a given use of the memory -> sparse heap can cause fragemntation, also external fragmentation because of the various sizes of the page tables

## Multi-level page tables

Idea : turn array into trees by making pages inside page tables

Benefits : more compact (only allocates space for non-blank pages of the page table) + memory doesn't have to be contiguous

Problems : **time-space tradeoff** -> more loads to get the information and complexity is increased for lookup

## Detailed example

Same calculation as for translating page teable entries, but it's the page table that is being indexed now. The directory contains the **physical frame number** of the page table itself

## More than two levels

If the page directory gets too big ...

With the TLB : no need to use the directories at all (direct VA - PA translation)

## Other concepts

### Inverted page tables

Adapted structure (e.g. hash table) of PFNs that gets searched every time

### Swapping

Temporarily writing memory to disk by putting pages in **kernel virtual space** (???)
