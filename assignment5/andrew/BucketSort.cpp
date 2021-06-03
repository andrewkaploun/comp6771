#include "BucketSort.h"

#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

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



void BucketSort::sort(unsigned int numCores) {
    std::sort(numbersToSort.begin(), numbersToSort.end(),
    
     [](const unsigned int& x, const unsigned int& y) {return aLessB(x, y, 0); });
}