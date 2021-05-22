/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <bits/stdc++.h>

// we better include the iterator
#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)

template <typename T> 
class btree {


 public:
  /** Hmm, need some iterator typedefs here... friends? **/
    friend class btree_iterator<T>;
    typedef btree_iterator<T> iterator;
    typedef btree_iterator<T> const_iterator; // surely this should be const_btree_iterator????!!!



  /**
   * Constructs an empty btree.  Note that
   * the elements stored in your btree must
   * have a well-defined copy constructor and destructor.
   * The elements must also know how to order themselves
   * relative to each other by implementing operator<
   * and operator==. (These are already implemented on
   * behalf of all built-ins: ints, doubles, strings, etc.)
   * 
   * @param maxNodeElems the maximum number of elements
   *        that can be stored in each B-Tree node
   */
  btree(size_t maxNodeElems = 40);

  /**
   * The copy constructor and  assignment operator.
   * They allow us to pass around B-Trees by value.
   * Although these operations are likely to be expensive
   * they make for an interesting programming exercise.
   * Implement these operations using value semantics and 
   * make sure they do not leak memory.
   */

  /** 
   * Copy constructor
   * Creates a new B-Tree as a copy of original.
   *
   * @param original a const lvalue reference to a B-Tree object
   */
  btree(const btree<T>& original);

  /** 
   * Move constructor
   * Creates a new B-Tree by "stealing" from original.
   *
   * @param original an rvalue reference to a B-Tree object
   */
  btree(btree<T>&& original);
  
  
  /** 
   * Copy assignment
   * Replaces the contents of this object with a copy of rhs.
   *
   * @param rhs a const lvalue reference to a B-Tree object
   */
  btree<T>& operator=(const btree<T>& rhs);

  /** 
   * Move assignment
   * Replaces the contents of this object with the "stolen"
   * contents of original.
   *
   * @param rhs a const reference to a B-Tree object
   */
  btree<T>& operator=(btree<T>&& rhs);

  /**
   * Puts a breadth-first traversal of the B-Tree onto the output
   * stream os. Elements must, in turn, support the output operator.
   * Elements are separated by space. Should not output any newlines.
   *
   * @param os a reference to a C++ output stream
   * @param tree a const reference to a B-Tree object
   * @return a reference to os
   */
//  template<typename T>
  friend std::ostream& operator<< (std::ostream& os, const btree<T>& tree) {
      return os;
  }

  /**
   * The following can go here
   * -- begin() 
   * -- end() 
   * -- rbegin() 
   * -- rend() 
   * -- cbegin() 
   * -- cend() 
   * -- crbegin() 
   * -- crend() 
   */
  //todo
    iterator begin() const {
        return iterator(nullptr, (this)); //todo getFirstVal()
    }
    iterator end() const {
        return iterator(nullptr, (this));
    }

    const_iterator cbegin() const {
        return const_iterator(nullptr, (this));//todo getFirstVal()
    }
    const_iterator cend() const {
        return const_iterator(nullptr, (this));
    }


  /**
    * Returns an iterator to the matching element, or whatever 
    * the non-const end() returns if the element could 
    * not be found.  
    *
    * @param elem the client element we are trying to match.  The elem,
    *        if an instance of a true class, relies on the operator< and
    *        and operator== methods to compare elem to elements already 
    *        in the btree.  You must ensure that your class implements
    *        these things, else code making use of btree<T>::find will
    *        not compile.
    * @return an iterator to the matching element, or whatever the
    *         non-const end() returns if no such match was ever found.
    */
  iterator find(const T& elem) {
      return iterator(nullptr, (this));
  }
    
  /**
    * Identical in functionality to the non-const version of find, 
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
  const_iterator find(const T& elem) const {
      return const_iterator(nullptr, (this));
  }
      
  /**
    * Operation which inserts the specified element
    * into the btree if a matching element isn't already
    * present.  In the event where the element truly needs
    * to be inserted, the size of the btree is effectively
    * increases by one, and the pair that gets returned contains
    * an iterator to the inserted element and true in its first and
    * second fields.  
    *
    * If a matching element already exists in the btree, nothing
    * is added at all, and the size of the btree stays the same.  The 
    * returned pair still returns an iterator to the matching element, but
    * the second field of the returned pair will store false.  This
    * second value can be checked to after an insertion to decide whether
    * or not the btree got bigger.
    *
    * The insert method makes use of T's copy constructor,
    * and if these things aren't available, 
    * then the call to btree<T>::insert will not compile.  The implementation
    * also makes use of the class's operator== and operator< as well.
    *
    * @param elem the element to be inserted.
    * @return a pair whose first field is an iterator positioned at
    *         the matching element in the btree, and whose second field 
    *         stores true if and only if the element needed to be added 
    *         because no matching element was there prior to the insert call.
    */
  std::pair<iterator, bool> insert(const T& elem){
      return {iterator(nullptr, (this)), true};
  }

  /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation. 
    * Check that your implementation does not leak memory!
    */
  ~btree();
    /*
   * reverse iterator
   */

    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    reverse_iterator rbegin() {
        return reverse_iterator(end());//return the last element
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

private:

    //todo
    std::shared_ptr<T> getFirstVal() {
        return nullptr;
    }
    class BtreeNode {
        // what i reckon we'll do is have an initial value <T> that will be the first sub-bst,
        // then have a list or set of pair<T, BtreeNode>, where it corresponds like in the
        // picture. so really this is like set<pair<T, shared_ptr<BtreeNode>>>
        //  the T doesnt need to be a shared_ptr, right?
      public:
        std::shared_ptr<BtreeNode> first;
        std::set<std::pair<std::shared_ptr<T>, std::shared_ptr<BtreeNode>>> l;
    };

    std::shared_ptr<T> next(std::shared_ptr<T> p) const {
        return p;
    }



};

template<typename T> btree<T>::btree(size_t maxNodeElems) {

}

template<typename T> btree<T>::btree(const btree<T>& original){

}


template<typename T> btree<T>::btree(btree<T>&& original) {

}
//todo
template<typename T> btree<T>& btree<T>::operator=(const btree<T>& rhs){
    return btree<T>();
}
//todo
template<typename T> btree<T>& btree<T>::operator=(btree<T>&& rhs) {
    return btree<T>();
}
////todo
//template<typename T> btree_iterator<T> btree<T>::find(const T& elem) {
//    return btree_iterator<T>::btree_iterator(nullptr);
//}
////todo
//template<typename T> btree_iterator<T> btree<T>::find(const T& elem) const {
//    return btree_iterator<T>::btree_iterator(nullptr);
//}
//todo
//template<typename T> std::pair<btree_iterator<T>, bool> btree<T>::insert(const T& elem) {
//    return { btree_iterator<T>::btree_iterator(nullptr), true};
//}
template<typename T> btree<T>::~btree() {

}

//template<typename T> std::ostream& operator<< (std::ostream& os, const btree<T>& tree){
//    return os;
//}
#endif
