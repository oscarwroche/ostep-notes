# Processes

A process is an abstraction of a running program.
There is an API for each process : Create / Destroy / Wait / Misc Control / Status

Processes are loaded from a disk into memory (lazily using paging / swapping), memory is allocated (resp. freed) using `malloc`(resp. `free`)

## Process States

Each process can have three states : Running / Ready / Blocked
Often a program will run until it requires an external action (for example I/O) and then be blocked, which will allow another Ready program to get Running. 

## Process lists etc ...

A data structure often called **Process list** or **PCB** (Process Control Block) stores the state of each process, including :

-   The register context
-   The process state
-   Information about size / stack / heap etc ... and more

A **context switch** is the act of restoring the register context of a process when it resumes running.
