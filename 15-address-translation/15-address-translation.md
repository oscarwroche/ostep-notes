# How to build an efficient virtualization of memory ?

**address translation** is the process of trnasforming vitual addresses into physical addresses.

## Simple model + assumptions

*  User's address space is **contiguous** in memory
*  It's smaller than the physical memory

## Example

```c
void func() {
int x = 3000; // thanks, Perry.
x = x + 3; // line of code we are interested in
...
```

is translated into assembly (use -fomit-frame-pointer flag to get this simple version) :

```assembly
128: movl 0x0(%ebx), %eax ;load 0+ebx into eax
132: addl $0x03, %eax ;add 3 to eax register
135: movl %eax, 0x0(%ebx) ;store eax back to mem
```

## Two types of relocation 

Dynamic / hardware-based : based on the **base** and **bounds** registers in each CPU.
The OS, when starting to run a program, decides what the **base address** is and puts it in the register. Subsequent memory references are translated : `physical address = virtual address + base`. The **bounds** helps for **protection** - checking if the generated addresses are within the bounds of the allocated memory.

Static / software-based : take the assembly code and generate a new one with the appropriate addresses. Not very efficient because of the possibility for the program to access forbidden addresses, also relocation not possible at runtime (which is sometimes useful).


This is all the basis of the **MMU (memory management unit)**.

## Kernel vs user mode

A bit in the CPU indicates what mode the CPU is running in : the **processor status word**
The instructions allowing to operate the address translation are run in **kernel mode**

The CPU should be able to generate **exceptions** in case some addresses are **out of bounds** (usually terminating the process)

## Other OS issues

OS has to find the address space, which given the assumptions (contiguous memory) is easy (finding free entry in array of slots and marking it as used), and put it back on the free list once the process is done.

The OS must also save and restore the base and bounds register for each context switch (using PCB, etc ...)

## Summary 

|Hardware Requirements | Notes |
----------------------------------------------------------
|Privileged mode | Needed to prevent user-mode processes from executing privileged operations |
|Base/bounds registers | Need pair of registers per CPU to support address translation and bounds checks |
|Ability to translate virtual addresses and check if within bounds | Circuitry to do translations and check limits; in this case, quite simple |
|Privileged instruction(s) to update base/bounds | OS must be able to set these values before letting a user program run |
|Privileged instruction(s) to register exception handlers | OS must be able to tell hardware what code to run if exception occurs |
|Ability to raise exceptions | When processes try to access privileged instructions or out-of-bounds memory |

## Inefficiencies ?

*  Space between stack and heap is wasted (internal fragmentation) -> solved by **segmentation** (see next chapter)
