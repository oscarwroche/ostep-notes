# How to speed up address translation when paging - avoiding extra memory references ?

The **translation-lookaside** buffer is used for these purposes - used as a cache for virtual-to-physical address translations.

## The basic algorithm

*  Extract VPN
*  Look it up in TLB
	* If it is in TLB -> OK
	* Else do normal procedure, add address to TLB and retry

## Example : accessing an array

*  Storing an element in the TLB may make life easier for elements on the same page - **spatial locality**
*  There will be a TLB miss every X elements, where X is the page size

Caches in general take advantage of spatial / temporal **locality**
Caches have to be kept small or they might defeat their original purpose
After a first access of the array, there won't be any TLB misses -> temporal locality

## How to handle misses - hardware or OS ?

*  **CISC** : handled by the hardware, via page-table register
*  **RISC** : software-managed TLB : exception + trap handler + look again at return-from-trap (a bit different from usual because the instruction that triggered the trap has to be retried). This is more flexible and simpler in terms of data structures

What if TLB miss-handling code itself generates a TLB miss etc ... ? Keep this code in physical memory or have an entry for it in the TLB from the start (**wired translations**)

## What's in the TLB exactly ?

An entry looks as follows : VPN | PFN | *other bits*

*other bits* = valid bit + protection bits (+ address space identifier (**ASID**) + dirty bit ...)

## How to handle context switches ?

TLB entries for a given process are irrelevant for others (except maybe wired address)

Solutions :

*  Flush the TLB every time -> safe but lots of misses
*  Use the **ASID** -> safe but there must be a register to save the current ASID

Sometimes process do share some memory (e.g. code sharing)

## When / how to replace the TLB entries ?

*  LRU, etc ... (see chapters of swapping)

## Lessons learned

Because of TLBs, **RAM isn't always RAM** !!!

Issues :

*  Large number of pages in short amount of time : **TLB coverage exceeded** -> more sophisticated **DBMS** might be necessary
*  Having a **physically-indexed cache** can becone a bottleneck -> this can be virtualized, etc ...
