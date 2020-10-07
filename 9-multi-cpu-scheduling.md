# How to schedule to share the CPU proportionally ?

## Tickets = share

Giving percentage of tickets to processes to give them a percentage of chances of getting the CPU (more like shares).
Random methods like that are useful because they can help avoiding some edge cases of deterministic methods and they're lightweight. However they tend to be bad at responding to quick, changing demands.

## Mechanisms

*  Tickets by user, then for each user by process ("different currencies")
*  Ticket transfer (to give more CPU from one process to another)
*  Ticket inflation (for one process to increase its ticket's value)

## Implementation

Linked list of {job, tickets} structs, go to next while total "index" < winner (with highest number of tickets first -> less iterations).

## Example

*   2 jobs with 100 tickets each
*   **fairness** metric : time(first job finished)/time(second job finished) - the closest F is to 1 the better

Fairness goes up with job lengths

### How to assign tickets ?

Open question

## Deterministic scheduling

*  Stride scheduling : divide large number by number of tickets to compute **stride**, set **pass** value to 0 for each job.

```c
curr = remove_min(queue); // pick client with min pass
schedule(curr); // run for quantum
curr->pass += curr->stride; // update pass using stride
insert(queue, curr); // return curr to queue
```

Programs will run with a frequency that is proportional to their ticket proportion.

## The Linux Completely Fair Scheduler (CFS)

Overhead (usually ~ 5%) associated with scheduling that has to be minimized.
*  Processes each accumulate **vruntime**, and the process with least **vruntime** gets to run

Tradeoff : if CFS switches often -> ++ fairness but ++ context switch time (resp. -- switches -> -- fairness -> ++ context switch time)

*  **sched_latency** : parameter to determine length for which CFS is completely fair (applied naively as above)
*  **min_granularity** : lower bound on time slice length (to avoid too many context switches if too many processes)

These two parameters guarantee some degree of fairness over **sched_latency**, while tracking **vruntime** so that process that didn't get to run on a **sched_latency** will run on the next one.

CFS also has frequent (~ every 1 ms) to see if current job has reached end of **min_granularity** / **sched_latency**

CFS allows user to use **nice** to change the rate at which **vruntime** increases for each process.

### How to increase performance of CFS ?

*  CFS uses **red-black trees** : binary tree that tries to maintain low depth. Using list requires for it to be ordered every time (to find minimum **vruntime**). O(log(n)) vs O(n)
*  Sleeping processes : if a process sleeps for a long time, its **vruntime** will fall behind and will monopolize CPU when resumed - setting the **vruntime** to the minimal **vruntime** of the other running processes limits this phenomenon.
