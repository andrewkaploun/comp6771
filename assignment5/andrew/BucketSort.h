/*pseudocode:

lets say there's n threads, and n is a power of 2  here's what we do:

n threads will split their sets into n buckets each.

 How will we know which numbers to put in these buckets?

 what we clearly want to do is make this into 9-10 buckets grouped by the most
significant digit. Now, we merge every bucket of its kind, and process them in parallel.

So, we place them into so-called 'big buckets'

yeah ok the hard part of this assignment is definitely making a good (potentially stable ) algo

ok so we clearly dont want to follow the exact idea of the textbook, but the general idea is:
 - group the numbers into N buckets based on the most significant radixes in parallel. 
 - sort the n buckets individually.

i think we kinda have no choice but to split it into, lets say for 4 cores, a bucket for [1, 2], [3,4], [5, 6,7] [8,9]
or, the buckets could lexicographically be bound by  say [0, 25), [25, 50), [50, 75), [75, inf) although generalising
to n would be a pain for that.

When you do that, you do the separation into some buckets, then voila, you're done.





 









an easy micro-optimisation: store the ints as 64-bit ints. then, there's a maximum of 10 digits,
one of them being 3 bits (0 to 4), so we only need 9*4+3 <= 64 bits to store each integer 'nicely'



*/


#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <vector>

struct BucketSort {
    // vector of nums
    std::vector<unsigned int> numbersToSort;
    void sort(unsigned int numCores);
};
#endif /* BUCKET_SORT_H */