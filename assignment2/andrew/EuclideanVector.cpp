#include "EuclideanVector.hpp"

namespace evec{

// double *vector;
// unsigned int size;


// template <class Iter> EuclideanVector::EuclideanVector (Iter begin, Iter end) 
//     : EuclideanVector(std::distance(begin, end))  {

//     for (unsigned int i = 0; i < size; i++) {
//         vector[i] = *begin++;
//     }
// }

EuclideanVector::EuclideanVector(unsigned int n) {
    vector = new double[n];
    size = n;
}

EuclideanVector::EuclideanVector(unsigned int n, double d) : EuclideanVector(n) {
    for (unsigned int i = 0; i < n; i++) {
        vector[i] = d;
    }
}


EuclideanVector::EuclideanVector(std::initializer_list<double> l) : EuclideanVector(l.begin(), l.end()){}

EuclideanVector::EuclideanVector(const EuclideanVector& c) : EuclideanVector(c.getNumDimensions()) {
    for (unsigned int i = 0; i < size; i++) {
        vector[i] = c[i];
    }
}

EuclideanVector::EuclideanVector(EuclideanVector&& c) {
    vector = c.vector;
    size = c.size;

    // now c will get destroyed
    c.vector = nullptr;
    c.size = 0;
    
}

EuclideanVector::~EuclideanVector() {
    // if (size != 0)
        delete [] vector;
}


double & EuclideanVector::operator[](const unsigned int i) {
    return vector[i];
}

const double & EuclideanVector::operator[](const unsigned int i) const {
    return const_cast<double&>(vector[i]);
}

EuclideanVector& EuclideanVector::operator+= (const EuclideanVector& other) {
    assert(getNumDimensions() == other.getNumDimensions());
    for (unsigned int i = 0; i < size; i++) {
        vector[i] += other[i];
        // std::cout << "meme "<<vector[i]<<std::endl;
    }
    return *this;
}

EuclideanVector& EuclideanVector::operator-= (const EuclideanVector& other) {
    assert(getNumDimensions() == other.getNumDimensions());
    for (unsigned int i = 0; i < size; i++) {
        vector[i] -= other[i];
        // std::cout << "meme "<<vector[i]<<std::endl;
    }
    return *this;
}

EuclideanVector& EuclideanVector::operator*= (double multiplicand ) {
    for (unsigned int i = 0; i < size; i++) {
        vector[i] *= multiplicand;
        // std::cout << "meme "<<vector[i]<<std::endl;
    }
    return *this;
}

EuclideanVector& EuclideanVector::operator/= (double multiplicand ) {
    for (unsigned int i = 0; i < size; i++) {
        vector[i] /= multiplicand;
        // std::cout << "meme "<<vector[i]<<std::endl;
    }
    return *this;
}

bool EuclideanVector:: operator== (const EuclideanVector& other) const {
    if (other.getNumDimensions() != this->getNumDimensions()) {
        return false;
    }

    for (unsigned int i = 0; i < this->getNumDimensions(); i++) {
        if (this[i] != other[i]) {
            return false;
        }
    }

    return true;
}

bool EuclideanVector:: operator!= (const EuclideanVector& other) const {
    return !(*this == other);
}

// make this &&
EuclideanVector EuclideanVector::operator+ (const EuclideanVector& other) const {
    auto sum = EuclideanVector(*this);
    sum += other;
    return sum;
}
//
EuclideanVector EuclideanVector::operator- (const EuclideanVector& other) const {
    auto sum = EuclideanVector(*this);
    sum -= other;
    return sum;
}
// todo add second one like we say we have to below
EuclideanVector EuclideanVector::operator* ( double other) const {
    auto product =   EuclideanVector(*this);
    product *= other;
    return product;
}
//
EuclideanVector EuclideanVector::operator/ (double other) const {
    auto dividend =  EuclideanVector(*this);
    dividend /= other;
    return dividend;
}
//todo 
double EuclideanVector::operator* (const EuclideanVector& other) const {
    assert(getNumDimensions() == other.getNumDimensions());
    double sum = 0;
    for (unsigned int i = 0; i < getNumDimensions(); i++) {
        sum += vector[i] * other[i];
    }
    return sum;
}

std::ostream& operator<<(std::ostream& os, EuclideanVector const & tc) {
    if (tc.size == 0) {
        os << "[]" << std::endl;
        return os;
    }
    os << "[" << tc[0];
    for (unsigned int i = 1; i < tc.getNumDimensions(); i++) {
        os << " " << tc[i];
    }
    os << "]" << std::endl;

    return os;
}

EuclideanVector::operator std::vector<double> () {
    std::vector<double> v(size);
    for (unsigned int i = 0; i < size; i++) {
        v[i] = vector[i];
    }
    return v;
}

EuclideanVector::operator std::list<double> () {
    std::list<double> l;
    for (unsigned int i = 0; i < size; i++) {
        l.push_back(vector[i]);
    }
    return l;
}

double EuclideanVector:: get(unsigned int i) const {
    return vector[i];
}

double EuclideanVector::getEuclideanNorm() const {
    double sum = 0;
    for (unsigned int i = 0; i < size; i++) {
        sum += (vector[i] * vector[i]);
    }
    return sqrt(sum);
}

unsigned int EuclideanVector::getNumDimensions() const {
    return size;
}

EuclideanVector EuclideanVector::createUnitVector() {
    return (*this) / this->getEuclideanNorm();
}

};


// todo a * vector and vector * a both ways hmmm