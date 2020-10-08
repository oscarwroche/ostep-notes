# An abstraction for multiprogramming on top of a single shared physical memory

*  First approach : store all program data on HD when switching processes -> too slow
*  Second approach : have a different "zone" of memory for each process in RAM

Issue : protection of each process' memory

## The address space

*  Contains all the memory state (code, stack, heap) of the running program
*  Code, heap that grows from the top and then stack that grows from bottom

The OS has to make sure that the **virtual addresses** requested from programs is translated to actual **physical addresses**

## Goals of memory virtualization

*  **Transparency** : programs should behave as if they had their own physical memory
*  **Efficiency** : time (programs shouldn't wait for too long) and space (not too much memory for virtualization structures)
*  **Protection** : protect OS memory from programs + programs shouldn't be able to access each others' memories -> **isolation**

Various **mechanisms** and **policies** allow to guarantee these properties

Note : microkernels take the principle of isolation to the extreme by having independent parts of the OS
Note : all addresses seen in C programs are virtual
