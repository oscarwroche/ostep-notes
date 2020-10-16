# How to virtualize memory with pages to avoid segmentation ?

The idea is to use fixed size parts of memory called pages

## Example

Pages are a virtual construct (the pages in a virtual addres space do not reflect how they actually are in physical memory)

Physical space is divided into **page frames** that are supposed to host pages

The OS keeps a per-process **page table** ot know where each of the pages are

Any virtual address is divided into a **VPN (virtual page number)** and an **offset**

*  Example : `mov 21, %eax` -> 21 translates to 010101 : the first 01 means "page 1" and the remaining 0101 means offset 5. "vrirtual page 1" is then translated using the page table

## Storage

* The page table can get very large : for a 32-bit address space the addres is divided into a 20-bit VPN and a 12-bit address space -> hte page table should have 2^20 entries ~ 4MB if each entry is 4 bits

## What's in the page table ?

*  List : **linear page table** - index is VPN, the **PTE (page table entry)** is used to find the **PFN (physical frame number)**
*  Content of PTEs : one **valid bit** to track if memory address is used (otherwise trap terminates process) + **protection bits** + **present bit** (to know whether the page is in RAM or disk) + **dirty bit** (has page been modified) + **reference / accessed bit** (has page been accessed : useful for page replacement). For x86, more details in Intel Architecture Manuals.

## Speed

Example :

```c
VPN = (VirtualAddress & VPN_MASK) >> SHIFT
PTEAddr = PageTableBaseRegister + (VPN * sizeof(PTE))
offset = VirtualAddress & OFFSET_MASK
PhysAddr = (PFN << SHIFT) | offset
```

... just to load an address from memory

## Memory tracing an example

(see 16-array.md)

As the loops goes on, the successive page tables 39 to 42 will be accessed, as well as the successive addresses of the array.
