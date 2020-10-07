# How to schedule without perfect knowledge

In the previous chapter, it was assumed that the running time of each process is known - this is not the case in general : how to schedule accordingly ?

## The rules

1.   Different queues - each with a priority level
2.   Jobs run according to decreasing priority and **run in RR** in case of equal priorities

The algorithm sets priorities based on observed behaviors.

3.   When a job enters the system, it's put in the topmost (highest priority) queue
4.   If a job uses an entire time slice (probably non-interactive) its priority is reduced
5.   If a job gives up the CPU before the end of the time slice, its priority is kept at the same level

### Examples

*   Single long-running job - job keeps decreasing priority every time slice until it reaches bottom priority
*   Single long-running job + short job coming - same but new job will take CPU because first job has reached lowest priority

MLFQ approximates SJF at first sight because of these examples

*   Single long-running job + repeated job with I/O - same but I/O will periodically take CPU because first job has reached lowest priority and new job releases CPU early

## Issues with the approach

*  Starvation : if there are always jobs in the top-priority queue then jobs from the other queues will never get CPU time
*  Somebody can write a program relinquishing the CPU (making some useless I/O) regularly 
*  Jobs with changing behavior are not handled well


### Adding priority boost

*  After a given time period **S**, push all jobs into top-priority queue

Forces RR behaviour with jobs in the lowest priority queues + allows to reevaluate the behavior of all processes (e.g. if a job stuck in the bottom queue needs interactive behavior)

How to choose S ? Too high : starvation / too low : unresponsive

### Preventing gaming

*  Change rules 4 and 5 to tracking globally the time used by each process - once a given amount of CPU time is used, the process is automatically demoted to a lower-priority queue

## How to choose MLFQ hyperparameters ?

A few tips :

*  Different queues can have different time slices (larger for lower-priority queues)
*  **Solaris MLFQ** : 60 queues, time slices increasing from 20 ms to a few hundres ms + priority boosting every 1 second
*  Automatic adjusting of parameters is possible (**decay-usage algorithms**)
*  Restrictions on the scheduler : reserve upper queues for system work, allow users to help set priorities (see CLI utility **nice**)
