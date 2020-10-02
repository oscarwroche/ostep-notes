## Theme : how to create and control processes ?

2 main system calls : `fork()` and `exec()` + `wait()`

### `fork`

fork creates a child process that starts **where it was called**, returns a value of zero to the child , and the PID of the child to the parent
The order in which the processes output is not deterministic and is linked to the **CPU scheduler**

### `wait`

`wait` tells the process to wait for its child processes to finish running - the parent process will stay stuck at the `wait` instruction until the child has finished. This allows to have a deterministic output.

### `exec`

exec calls another function but does not return - the heap / stack of the current function are simply replaced with the ones of the function called by exec but it doesn't return to the next instruction after (if it succeeds).

example : the **shell** when called with a command, uses `fork` to have a new process, uses `exec` in the child process and `wait` in the parent process to print a new prompt

other example : using `fork` and `exec` allows to have instructions between the two- for example closing the standard output to allow to pipe instructions
