# How to keep control over the system while running programs ?

## Limited direct executions

|OS 			       |	Program|
-------------------------------|------------------------
|Create entry for process list |
|Allocate memory for program   |
|Load program into memory      |
|Set up stack with argc/argv   |
|Clear registers               |
|Execute call main()           |
|			       |	Run main() |
|			       | 	Execute return from main |
|Free memory of process        |
|Remove from process list      |

## How to make sure the program doesn't do unwanted things

Example : the OS wants to allow programs to do I/O without giving full control over the system.

2 modes :

* User mode : restricted, no I/O requests
* Kernel mode : anything goes

**System calls** allows to go between the two of them.
A system call contains a **trap** and a **return-from-trap** instruction.
The trap pushes registers relative to the code on a **kernel stack**, and the return-from-trap instruction will pop them to resume execution of the caller.

A **trap table** specifies what the hardware should do when some events happen, i.e. a system call or an interrupt happens. **System call numbers** are used to only allow a few select operations to be made.

When using a trap, the processor pushes the program counter / flags / register of the trapped process on its **kernel stack**.

## How to switch between processes ?

Cooperative approach : wait for system calls - each program explicitly **yields** control to the OS or transfer control when doing something illegal. Problems for infinite loops etc ... where the OS never takes back control.

Non-cooperative approach : **timer interrupt** every X milliseconds. OS regains control and decides whether to continue or stop the current process.

This decision is made using the **scheduler** (see next chapter). Switching between processes is made using a low-level **context switch**. The OS saves the register values of the currently-executing process and restores some from the process that is about to be executed.

## What about concurrency ?

See **locking schemes**
