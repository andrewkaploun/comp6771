#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
#include "btree.h"


/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template <typename T> class btree;

template <typename T> class btree_iterator {
public:
    typedef std::ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    // Idk if i need these things above

// oh lmao i just didnt do an assignemnt fo riterators
    reference operator*() const;
    pointer operator->() const { return &(operator*()); }
    btree_iterator& operator++() ;
//    btree_iterator operator++(int) ;
    btree_iterator& operator--();
//    btree_iterator operator--(int);
    bool operator==(const btree_iterator& other) const;
    bool operator!=(const btree_iterator& other) const { return !operator==(other); }
    explicit btree_iterator(typename std::shared_ptr<T> p = nullptr,
        const std::shared_ptr<typename btree<T>::BtreeNode> root_ = nullptr) : p_(p), root(root_) {}
private:
    typename std::shared_ptr<T> p_;
    const  std::shared_ptr<typename btree<T>::BtreeNode> root;

};


template <typename T> typename btree_iterator<T>::reference btree_iterator<T>::operator*() const {
    return *p_;
}

template <typename T> btree_iterator<T>& btree_iterator<T>::operator++() {
    assert(p_ != nullptr);
    p_ = root->next(p_);
    return *this;
}
//
//template <typename T> btree_iterator<T> btree_iterator<T>::operator++(int) {
//    assert(p_ != nullptr);
//    p_ = root->next(p_);
//    return btree_iterator<T>(p_, root);
//}
//

template <typename T> btree_iterator<T>& btree_iterator<T>::operator--() {
//    assert(p_ != nullptr);
    if (p_ == nullptr) {
        p_ = (root->largest());
    }
    p_ = root->prev(p_);
    return *this;
}
//
//template <typename T> btree_iterator<T> btree_iterator<T>::operator--(int) {
////    assert(p_ != nullptr);
//    if (p_ == nullptr) {
//        p_ = (root->largest());
//    }
//    p_ = root->prev(p_);
//    return btree_iterator<T>(p_, root);
//}

template <typename T> bool btree_iterator<T>::operator==(const btree_iterator<T>& other) const {
    return p_ == other.p_;
}




template <typename T> class const_btree_iterator {
public:
    typedef std::ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    // Idk if i need these things above


     reference operator*() const;
     pointer operator->() const { return &(operator*()); }
    const_btree_iterator& operator++();
    const_btree_iterator& operator--();
    bool operator==(const const_btree_iterator& other) const;
    bool operator!=(const const_btree_iterator& other) const { return !operator==(other); }
    explicit const_btree_iterator(typename std::shared_ptr<T> p = nullptr) : p_(p) {}
private:
    typename std::shared_ptr<T> p_;

};


template <typename T> typename const_btree_iterator<T>::reference const_btree_iterator<T>::operator*() const {
    return *p_;
}

template <typename T> const_btree_iterator<T>& const_btree_iterator<T>::operator++() {
    assert(p_ != nullptr);
    p_ = btree<T>::next(p_);
    return *this;
}

template <typename T> const_btree_iterator<T>& const_btree_iterator<T>::operator--() {
// todo: we dont ever actually use this, right? i hope? rip

    assert(p_ != nullptr);
    p_ = btree<T>::next(p_);
    return *this;
}

template <typename T> bool const_btree_iterator<T>::operator==(const const_btree_iterator<T>& other) const {
    return p_ == other.p_;
}




#endif
