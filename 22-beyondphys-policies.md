# How to decide which pages to evict from memory ?

## Cache management

The main memory can be viewed as a cache for all the virtual memory pages - how which we'll try to maximize the hits.

Metric used : **AMAT (Average Memory Access Time)** = T(memory) + P(miss)xT(disk)

## Optimal replacement policy

Replace page that will be accessed furthest in the future

Types of misses : **cold start** / **capacity** / **conflict**

Theoretical policy that is useful for measuring the performance of other real-world policies

## FIFO policy

Queue system - simple but inefficient.
Interesting : performance doesn't increase with cache size - because queues don't have **stack property**, i.e. a stack of size n+1 contains a stack of size n so its performance can only better

## Random policy

Also simple to implement but only slightly more efficient than FIFO
Problem with both approaches : can easily kick out important page

## LRU policy

**Principle of locality** : some data structures are used frequently in succession (tempploral locality here)

## Examples with larger workloads

*  No locality workload (completely random pages)
All policies perform the same because there is no locality that would allow LRU to perform better

*  80 / 20 workload (20% of pages accessed 80% of the time)  
FIFO > others

*  Looping sequential workload (pages accessed in loop in same order)
Worst case for LRU and FIFO (0 hits if cache size is lower than number of pages in loop)

## How to actually implement LRU

LRU is very expensive is done exactly : additional structure must be kept on the side and looking for least-recently becomes slow when said structure gets too big

### How to approximate LRU

Hardware : add one use bit to each page - it is set to 1 when page is referenced (r/w)
Use **clock algorithm** : put pages in circular list and keep setting 1 use bits to 0 until a 0 is found.

* This algorithm can be modified by choosing to evict pages that are clean (not modified) - using the dirty bit

## Other policies

*  Page selection : demand paging
*  Clustering

## Thrashing - if demands excess physical memory

*  Constant paging - problem

Solutions :

*  Attempt to run only certain processed
*  Out-of-memory killer (kill process with worst memory usage)

# Conclusion : just buy more memory

