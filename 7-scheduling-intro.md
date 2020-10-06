# How to schedule policies (intuitively) ?

Some assumptions to make it a bit easier :

1. Each job runs for the same amount of time.
2. All jobs arrive at the same time.
3. Once started, each job runs to completion.
4. All jobs only use the CPU (i.e., they perform no I/O)
5. The run-time of each job is known.

Chosen metric : **turnaround time** (time(job completed) - time(job arrived)) with time(job arrived) = 0 in this case

Other (often orthogonal) metric : **fairness**

## Strategies

### FIFO

Turnaround time for 3 jobs arriving at the same time (lasting 10 sseconds each) is 20. But relaxing assumption 1 show the problem that a long-running job will block other short-running jobs (convoy effect).

### SJF (Shortest Job First)

Avoids convoy effect - theoretically optimal but problems in worst case when jobs don't arrive at the same time because it has to wait until jobs complete.

### STCF (Shortest Time-to-Completion First)

Assumption 3 is relaxed (jobs can thus be interrupted).

**Preemptive schedulers** : allow to stop one job to run another via a context switch - this is almost all schedulers.

This scheduler is preemptive, it can interrupt a long-running job with another if its time to completion is lower. (How to estimate this ?)

## With response time as a metric

The **response time** quantifies the time when a job is first run compared to its arrival time. It is of particular interest when there is a demand for an interactive system (i.e. a command line).

### Round robin scheduling

Jobs are run for a **time slice** that is a multiple of the timer interrupt.
This is good for response time but the slice shouldn't be too small because then the context switch will be too long compared to it. The process of choosing the time slice knowing this is called **amoritzation** (i.e. a context switch that is 10% of the time slice - increase time slice by 10%).

The turnaround is pretty bad because jobs tend to get streched out as muc has possible (if they are the same length).

In general **turnaround != fairness**

## Incorporating I/O

When a process initates I/O, it won't be using the CPU and should probably use the CPU for another process. Using the time of a blocked process to run another is called **overlap**.

Dividing jobs that contain I/O into sub-jobs, some CPU-intensive and some others not allows to have overlap.

## The scheduler **does not** know how long each job takes ...

See next chapter and the **multi-level feedback queue**.
