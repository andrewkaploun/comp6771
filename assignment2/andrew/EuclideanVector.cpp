#include "EuclideanVector.h"

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
    for (unsigned int i = 0; i < n; i++)
        vector[i] = 0;
}
EuclideanVector::EuclideanVector() :EuclideanVector(1) {}

EuclideanVector::EuclideanVector(unsigned int n, double d) : EuclideanVector(n) {
    for (unsigned int i = 0; i < n; i++) {
        vector[i] = d;
    }
}


EuclideanVector::EuclideanVector(std::initializer_list<double> l) : EuclideanVector(l.size()){
    auto it = l.begin();
    unsigned int i = 0;
    while( it != l.end()) {
        vector[i] = *it;
        i++;
        it++;
    }

}

EuclideanVector::EuclideanVector(const EuclideanVector& c) : EuclideanVector(c.getNumDimensions()) {
    for (unsigned int i = 0; i < size; i++) {
        vector[i] = c[i];
    }
}
//EuclideanVector& EuclideanVector::operator=(const EuclideanVector& c) {
//    return EuclideanVector(c);
//}
//
//EuclideanVector& EuclideanVector::operator=(EuclideanVector&& c) {
//    return EuclideanVector(c);
//}

EuclideanVector::EuclideanVector(EuclideanVector&& c) {
    this->vector = c.vector;
    this->size = c.size;

    // now c will get destroyed
    c.vector = nullptr;
    c.size = 0;
    
}

EuclideanVector::~EuclideanVector() {
    // if (size != 0)
    std::cout << " deleting "<<(unsigned long long) vector <<"of size "<<size<<" is "<<*this<<std::endl;
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
    std::cout << "this = "<<*this<<std::endl;
    std::cout<<"other = "<< other<< std::endl;
    if (other.getNumDimensions() != this->getNumDimensions()) {
        std::cout << " bad"<< this->getNumDimensions()<<" "<<other.getNumDimensions()<<std::endl;
        return false;
    }
    std::cout<< " here"<<std::endl;
    for (unsigned int i = 0; i < this->getNumDimensions(); i++) {
        std::cout << (*this)[i]<< " "<< vector[i]<<std::endl;
        if ((*this)[i] != other[i]) {
            std::cout << "returning false"<<std::endl;
            return false;
        }
    }
    std::cout<< " returning true"<< std::endl;
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
    assert(sum.getNumDimensions() == other.getNumDimensions() &&
    sum.getNumDimensions() == this->getNumDimensions());
    std::cout<< " applied the minus operation now minus is "<< sum<<std::endl;
    return sum;
}
// todo add second one like we say we have to below
EuclideanVector EuclideanVector::operator* ( double other) const {
    auto product =   EuclideanVector(*this);
    product *= other;
    return product;
}

//EuclideanVector operator*(double other, const EuclideanVector& m) const {
//    return m* other;
//}
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
        os << "[]" ;
        return os;
    }
    os << "[" << tc[0];
    for (unsigned int i = 1; i < tc.getNumDimensions(); i++) {
        os << " " << tc[i];
    }
    os << "]";

    return os;
}

EuclideanVector::operator std::vector<double> () const {
    std::vector<double> v(size);
    for (unsigned int i = 0; i < size; i++) {
        v[i] = vector[i];
    }
    return v;
}

EuclideanVector::operator std::list<double> () const {
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

EuclideanVector EuclideanVector::createUnitVector() const {
//    return EuclideanVector();
    return (*this) / this->getEuclideanNorm();
}
    EuclideanVector operator*(double other, const EuclideanVector& m)  {
    return m * other;
}
};


// todo a * vector and vector * a both ways hmmm