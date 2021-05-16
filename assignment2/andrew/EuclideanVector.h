
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


    EuclideanVector(unsigned int n, double d);

    EuclideanVector(std::list<double> l);
    EuclideanVector(std::initializer_list<double> l);
    EuclideanVector(const EuclideanVector& c);
    EuclideanVector& operator=(const EuclideanVector& c)  {
        size = c.getNumDimensions();
        vector = new double [size];
        for (unsigned int i = 0; i < c.getNumDimensions(); i++) {
            vector[i] = c[i];
        }
        return *this;
    };
    EuclideanVector& operator=(EuclideanVector&&c ) {
        this->vector = c.vector;
        this->size= c.size;

        c.vector = nullptr;
        c.size = 0;
        return *this;
    }
    EuclideanVector(EuclideanVector&& c);

    // this ends up beigna  better approach since templates mean that the compilation fails on EuclidenaVector(0,0);
    EuclideanVector (std::vector<double>::iterator begin, std::vector<double>::iterator end)
            : EuclideanVector(std::distance(begin, end))  {

        for (unsigned int i = 0; i < size; i++) {
            vector[i] = *begin++;
        }
    }

    EuclideanVector (std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end)
            : EuclideanVector(std::distance(begin, end))  {

        for (unsigned int i = 0; i < size; i++) {
            vector[i] = *begin++;
        }
    }

    EuclideanVector (std::list<double>::iterator begin, std::list<double>::iterator end)
            : EuclideanVector(std::distance(begin, end))  {

        for (unsigned int i = 0; i < size; i++) {
            vector[i] = *begin++;
        }
    }

    EuclideanVector (std::list<double>::const_iterator begin, std::list<double>::const_iterator end)
            : EuclideanVector(std::distance(begin, end))  {

        for (unsigned int i = 0; i < size; i++) {
            vector[i] = *begin++;
        }
    }

    EuclideanVector (std::initializer_list<double>::const_iterator begin, std::initializer_list<double>::const_iterator end)
            : EuclideanVector(std::distance(begin, end))  {

        for (unsigned int i = 0; i < size; i++) {
            vector[i] = *begin++;
        }
    }
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

    operator std::vector<double> () const;
    operator std::list<double> () const;

    double get(unsigned int i) const;
    double getEuclideanNorm() const;
    unsigned int getNumDimensions() const;
    EuclideanVector createUnitVector() const;

};
    EuclideanVector operator*(double other, const EuclideanVector& m)  ;
};

