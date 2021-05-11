#include<bits/stdc++.h>

namespace evec{

class EuclideanVector {
public:
    EuclideanVector(unsigned int n);
    template <class Iter> EuclideanVector (Iter begin, Iter end);


};
double *vector;
unsigned int size;


template <class Iter> EuclideanVector::EuclideanVector (Iter begin, Iter end) 
    : EuclideanVector(std::distance(begin, end))  {

    for (unsigned int i = 0; i < size; i++) {
        vector[i] = *begin++;
    }
}

EuclideanVector::EuclideanVector(unsigned int n) {
    vector = new double[n];
    size = n;
}
};



int main() {
        evec::EuclideanVector a(2); 
    std::list<double> l {1,2,3}; 

    evec::EuclideanVector b{l.begin(),l.end()}; 
    return 0;
}