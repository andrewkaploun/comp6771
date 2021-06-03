#include "BucketSort.h"

#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
#include <thread>
#include <mutex>

bool aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow) {
    if (x == y) return false;

    unsigned int a = x;
    unsigned int b = y;

    if ( pow ==0 ){
        while (a/10 > 0) a /= 10;
        while (b/10 > 0) b /= 10;



    } else {
        while (a/10 >= (unsigned int) std::round(std::pow(10, pow)))
            a /= 10;

        while (b/10 >= (unsigned int) std::round(std::pow(10, pow)))
            b /= 10;
    }

    if (a == b) 
        return aLessB(x, y, pow+1);
    else 
        return a < b;
    


}

unsigned int ith_digit(unsigned int n, unsigned int digit) { //0-indexed
    if (digit == 0){
          while (n/10 > 0) n /= 10;
        return n;
    }
    while (n/10 >=  std::round(std::pow(10, digit))) {
        n /= 10;
    }
    return n%10;
}

unsigned int first_2_digits(unsigned int i) {
    // std::cout << " first digit of "<< i << " is "<<ith_digit(i, 0)<<std::endl;
    return (ith_digit(i, 0)*10) + ith_digit(i, 1);
}


// One past the last element of the array of numbers that is associated with this core
// core is zero-indexed
size_t core_arr_interval_end(unsigned int core, unsigned int numCores, size_t nums) {
    core += 1;
    return ( (long long )core *(long long) nums )/ (long long) numCores;
}

// // One past the last num out of 99/100 that this cores bucket corresponds to
// // core is zero-indexed
// unsigned int core_nums_interval_end(unsigned int core, unsigned int numCores) {
//     core += 1;
//     return (double) core / (double) numCores * 100;
// }

void BucketSort::sort(unsigned int numCores) {
    // std::cout << " initially array is ";
    // for (auto i : numbersToSort) {
    //     std::cout << i << ' ';
    // }

    // std:: cout<< std::endl;




    numCores = std::min(numCores, (unsigned int) 8);

     //intermediate buckets used in the first part of the algo
    // unsigned int * initial_buckets = new unsigned int [10*numbersToSort.size()];
    
    //the big buckets as stated in the textbook
    unsigned int * buckets = new unsigned int [numCores*numbersToSort.size()]; 
    std::vector<unsigned int> buckets_index(numCores);
    std::vector<std::mutex> buckets_mutex(numCores);
    std::vector<std::thread> threads(10);
    unsigned int thread_id = 0;
    unsigned int divisor = 100/numCores +1;
    // bucket into intervals of 100/numcores for the first 2 digits
    // actually thats kinda bad since we then have to re-do the second digit, lol wtf.
    
    // so yeah with the 2 sets of buckets approach( what we will do), sure, we scan one of the digits once, but
    // we also save 1.5x the time so its fine.
    
    // The easy thing to do is simply to bucket each starting num in the range of 00, 99 by first_2_digits/divisor

    auto first = [&](unsigned int thread_id) {
        // std:: cout << "first thread id is "<< thread_id<<std::endl;
        size_t start_index = core_arr_interval_end(thread_id-1, numCores, numbersToSort.size());
        size_t end_index = core_arr_interval_end(thread_id, numCores, numbersToSort.size());
        // std::cout << " start index = "<< start_index << " end index = "<< end_index<<std::endl;
        for (size_t i = start_index; i < end_index; i++) {
            unsigned int bucket = std::min(first_2_digits(numbersToSort[i])/divisor, numCores - 1); 
            // std:: cout << " number "<< numbersToSort[i]<< " has first 2 digits "<< first_2_digits(numbersToSort[i])
            //     <<"  and goes into bucket "<<bucket<< std::endl;
            std::lock_guard<std::mutex> guard(buckets_mutex[bucket]);
            buckets[bucket *numbersToSort.size() + buckets_index[bucket]] = numbersToSort[i];
            // std::cout << "at thread id "<< thread_id << " and bucket "<< bucket << 
            //     " setting buckets["<<bucket  *numbersToSort.size() + buckets_index[bucket] << "] to "
            //     << numbersToSort[i]<< std::endl;

            buckets_index[bucket]++;
        }
    };
    
    for (unsigned int i = 0; i < numCores; i++) {
        threads[i] = std::thread{first, thread_id};
        thread_id++;
    }

    for (unsigned int i = 0; i < numCores; i++) {
        threads[i].join();
    }


    auto sort_buckets = [&](unsigned int thread_id) {
        // std::cout << " buckets before is "<< std::endl;
        // for (unsigned int i  = thread_id *numbersToSort.size(); i < thread_id*numbersToSort.size() + buckets_index[thread_id]; i++) {
        //     std::cout << buckets[i]<< " ";
        // }
        // std::cout<< std::endl;



        std::sort( &buckets[thread_id  *numbersToSort.size()], &buckets[thread_id * numbersToSort.size() + buckets_index[thread_id]],
            [](const unsigned int& x, const unsigned int& y) {return aLessB(x, y, 1); }); // zeroeth num is already done :)
        
        
        
        // std::cout << " buckets after is "<< std::endl;
        // for (unsigned int i  = thread_id *numbersToSort.size(); i < thread_id*numbersToSort.size() + buckets_index[thread_id]; i++) {
        //     std::cout << buckets[i]<< " ";
        // }
        // std::cout<< std::endl;
    };
    
    thread_id = 0;
    for (unsigned int i = 0; i < numCores; i++) {
        threads[i] = std::thread{sort_buckets, thread_id};
        thread_id++;
    }

    for (unsigned int i = 0; i < numCores; i++) {
        threads[i].join();
    }
    
    unsigned int start_index = 0;
    auto merge = [&](unsigned int thread_id, unsigned int start_index) {
        for (unsigned int i = 0; i < buckets_index[thread_id]; i++) {
            numbersToSort[start_index + i] = buckets[thread_id*numbersToSort.size() + i];
        }
    };

    thread_id = 0;
    for (unsigned int i = 0; i < numCores; i++) {
        threads[i] = std::thread{merge, thread_id, start_index};
        thread_id++;
        start_index += buckets_index[i];
    }

    for (unsigned int i = 0; i < numCores; i++) {
        threads[i].join();
    }


    // std::cout << " after sorting array is ";
    // for (auto i : numbersToSort) {
    //     std::cout << i << ' ';
    // }

    // std:: cout<< std::endl;
    delete[] buckets;
}