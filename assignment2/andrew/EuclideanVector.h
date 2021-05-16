
#pragma once
#include<bits/stdc++.h>

namespace evec{

class EuclideanVector {
    private:
    double *vector;
    unsigned int size;


public:
    EuclideanVector(unsigned int n);
    EuclideanVector();
    // template <class Iter> EuclideanVector (Iter begin, Iter end);
    template <class Iter> EuclideanVector (Iter begin, Iter end) 
        : EuclideanVector(std::distance(begin, end))  {

        for (unsigned int i = 0; i < size; i++) {
            vector[i] = *begin++;
        }
    }

    EuclideanVector(unsigned int n, double d);
 
    EuclideanVector(std::list<double> l);
    EuclideanVector(std::initializer_list<double> l);
    EuclideanVector(const EuclideanVector& c);
    EuclideanVector& operator=(const EuclideanVector& ) = default;
    EuclideanVector& operator=(EuclideanVector&& ) = default;
    EuclideanVector(EuclideanVector&& c);
    ~EuclideanVector();


    double &operator[](const unsigned int i);
    const double &operator[](const unsigned int i) const;
    EuclideanVector& operator+= (const EuclideanVector& other);
    EuclideanVector& operator-= (const EuclideanVector& other);
    EuclideanVector& operator*= (double multiplicand);
    EuclideanVector& operator/= (double multiplicand);
    bool operator== (const EuclideanVector& other) const;
    bool operator!= (const EuclideanVector& other) const;
    EuclideanVector operator+ (const EuclideanVector& other) const;
    EuclideanVector operator- (const EuclideanVector& other) const;
    EuclideanVector operator* (double other) const;
//    EuclideanVector operator*(double other, const EuclideanVector& m) const;
    EuclideanVector operator/ (double other) const;
    double operator* (const EuclideanVector& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, EuclideanVector const & tc);

    operator std::vector<double> ();
    operator std::list<double> ();

    double get(unsigned int i) const;
    double getEuclideanNorm() const;
    unsigned int getNumDimensions() const;
    EuclideanVector createUnitVector();

};
    EuclideanVector operator*(double other, const EuclideanVector& m)  {
        return m* other;
    }
};

