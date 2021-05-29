/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */
#define DEBUG memez

#ifdef DEBUG
#define mem std::cout<<"meme\n";
#define p1(a) std::cout<<#a<<"= "<<a<<std::endl
#define p2(a, b) std::cout<<#a<<"= "<<a<<" "<<#b<<"= "<<b<<std::endl
#define p3(a, b, c) std::cout<<#a<<"= "<<a<<" "<<#b<<"= "<<b<<" "<<#c<<"= "<<c<<std::endl
#define p4(a, b, c, d) std::cout<<#a<<"= "<<a<<" "<<#b<<"= "<<b<<" "<<#c<<"= "<<c<<" "<<#d<<"= "<<d<<std::endl
#define p5(a, b, c, d, e) std::cout<<#a<<"= "<<a<<" "<<#b<<"= "<<b<<" "<<#c<<"= "<<c<<" "<<#d<<"= "<<d<<" "<<#e<<"= "<<e<<std::endl
#define pa(arr); for(int i = 0; i < arr.size(); i++) std::cout<< arr[i]<<" "; std::cout<<std::endl;
#define pA(arr); for(int i = 0; i < arr.size(); i++) {for(int j = 0; j < arr[i].size(); j++)std::cout<<arr[i][j]; std::cout<<std::endl;}
#else
#define mem
#define p1(a)
#define p2(a, b)
#define p3(a, b, c)
#define p4(a, b, c, d)
#define p5(a, b, c, d, e)
#define pa(arr);
#define pA(arr);
#endif

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
  btree(const btree<T>& original) = default;

  /** 
   * Move constructor
   * Creates a new B-Tree by "stealing" from original.
   *
   * @param original an rvalue reference to a B-Tree object
   */
  btree(btree<T>&& original)= default;
  
  
  /** 
   * Copy assignment
   * Replaces the contents of this object with a copy of rhs.
   *
   * @param rhs a const lvalue reference to a B-Tree object
   */
  btree<T>& operator=(const btree<T>& rhs)= default;

  /** 
   * Move assignment
   * Replaces the contents of this object with the "stolen"
   * contents of original.
   *
   * @param rhs a const reference to a B-Tree object
   */
  btree<T>& operator=(btree<T>&& rhs)= default;

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
  friend std::ostream& operator<< (std::ostream& os, const btree<T>& tree)
  {
      for(iterator iter = tree.begin(); iter != tree.end(); ++iter) {
          os<< *iter<< ' ';
      }
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
        return iterator(root->smallest(), (root)); //todo getFirstVal()
    }
    iterator end() const {
        return iterator(nullptr, (root));
    }

    const_iterator cbegin() const {
        return const_iterator(root->smallest(), (root));//todo getFirstVal()
    }
    const_iterator cend() const {
        return const_iterator(nullptr, (root));
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
  iterator find(const T& elem) ;
//  {
//      return iterator(nullptr, (root));
//  }
//
  /**
    * Identical in functionality to the non-const version of find, 
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
  const_iterator find(const T& elem) const
  ;
//  {
//      return const_iterator(nullptr, (root));
//  }
      
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
  std::pair<iterator, bool> insert(const T& elem)
  ;
//      {
//          return {iterator(nullptr, (root)), true};
//      }

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
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    const_reverse_iterator crend() const {
        return const_reverse_iterator(begin());
    }

private:
    struct SharedComparatorN {
        bool operator()(const std::shared_ptr<T>& lhs,
                        const std::shared_ptr<T>& rhs) const
        {
            return *lhs < *rhs;
        }
    };

    size_t max_node_elems;
    //todo
    std::shared_ptr<T> getFirstVal() {
        return root->smallest();
    }
    // invariant: only the root can be empty.
    // be empty
    // invariant: things only point to lower nodes if they have filled up to their max size
    class BtreeNode {
        // what i reckon we'll do is have an initial value <T> that will be the first sub-bst,
        // then have a list or set of pair<T, BtreeNode>, where it corresponds like in the
        // picture. so really this is like set<pair<T, shared_ptr<BtreeNode>>>
        //  the T doesnt need to be a shared_ptr, right?


      public:

        BtreeNode(size_t max_node_elems_) : max_node_elems(max_node_elems_)

        ,l(std::map<std::shared_ptr<T>, std::shared_ptr<BtreeNode>, SharedComparatorN>{})
        {first = nullptr;
//        l = std::map<std::shared_ptr<T>, std::shared_ptr<BtreeNode>, SharedComparatorN>{};
//        if (l.size() != 0)
//        p2("meme", l.size());
        }

        std::shared_ptr<BtreeNode> first;
        size_t max_node_elems;
        std::map<std::shared_ptr<T>, std::shared_ptr<BtreeNode>, SharedComparatorN> l;



        std::shared_ptr<T> smallest() const {
            if (!l.size()) {
                return nullptr;
            }
            if (first != nullptr) {

                return first->smallest();
            }
            return l.begin()->first;
        }

        std::shared_ptr<T> largest() const {
            if (!l.size()) {
                return nullptr;
            }

            if (l.rbegin()->second != nullptr) {
                return l.rbegin()->second->largest();
            }
            return l.rbegin()->first;
        }
        std::shared_ptr<T> next(std::shared_ptr<T> p) const {
            /*
             *
             * pseudocode:
             * if p is in our list, get
             *  - the smallest thing in the subtree that follows it, if it exists
             *  - the next element in our list l, if it exists
             *
             *  otherwise return null
             *
             *  then, lets say p isnt in our list.
              get the next() for the node with  p in it. if this returned a result, return it, otherwise:
              return the first node thats next, and if it doesnt exist, return null


             *
             *
             */
            //std::prev(l.upper_bound(p),1) is the  latest thing equal to or before
            if (!l.size()) {
                return nullptr;
            }
            if (l.lower_bound(p) == l.end()) {
                return l.rbegin()->second->next(p);//probably dont need this idk, probably fucks up my time
            }
            if (l.upper_bound(p) == l.begin()) {
                if (first == nullptr) {
                    return l.upper_bound(p)->first;
                }
                auto maybe_null  = first->next(p);

                if (maybe_null == nullptr) {
                    return l.upper_bound(p)->first;
                }
                return maybe_null;
            }
            auto it = std::prev(l.upper_bound(p),1);
            if (it->first == p) {
                if (it->second != nullptr) {
                    return  it->second->smallest();
                } else if (std::next(it, 1) != l.end()) {
                    return std::next(it, 1)->first;
                } else {
                    return nullptr;
                }
            } else {
                if (it->second != nullptr) {
                    auto maybe_null = it->second->next(p);

                    if (maybe_null != nullptr) {
                        return maybe_null;
                    }

                }
                if (std::next(it, 1) != l.end()) {
                    return std::next(it, 1)->first;
                } else {
                    return nullptr;
                }
            }


        }

        std::shared_ptr<T> prev(std::shared_ptr<T> p) const {

            if (!l.size()) {
                return nullptr;
            }
            if (l.lower_bound(p) == l.begin()) {
                if (first == nullptr) {
                    return nullptr;
                }
                return first->prev(p);
            }
            //here
            if (l.lower_bound(p) == l.end()) {//here
                if (l.rbegin()->second == nullptr) {
                    return l.rbegin()->first;
                }
                auto maybe_null  = l.rbegin()->second->prev(p);

                if (maybe_null == nullptr) {
                    return l.rbegin()->first;
                }
                return maybe_null;
            }
            //here
            auto it = std::prev(l.lower_bound(p),1);// first thing lower than p
//            if (it->first == p) {
//                if (it->second != nullptr) {
//                    return  it->second->smallest();
//                } else if (std::next(it, 1) != l.end()) {
//                    return std::next(it, 1)->first;
//                } else {
//                    return nullptr;
//                }
//            } else {
                if (it->second != nullptr) {
                    auto maybe_null = it->second->prev(p);

                    if (maybe_null != nullptr) {
                        return maybe_null;
                    }

                }
                return it->first;
//                if (std::next(it, 1) != l.end()) {
//                    return std::next(it, 1)->first;
//                } else {
//                    return nullptr;
//                }
//            }


        }

        std::shared_ptr<T> find (const T& elem) const {
//            p1(l.size());
//            p2("here looking for ", elem);
            if (!l.size()) {
                return nullptr;
            }
            if (elem < *(l.begin()->first)) {
                if (first == nullptr) {//l.begin()->second->find(elem);
                    return nullptr;
                }
                return first->find(elem);
            }
            auto it = std::prev(l.upper_bound(std::make_shared<T>(elem)),1);
            if (*(it->first) == elem) {
//                p1(elem);
                return it->first;
            }
            if (it->second != nullptr) {
                return (it->second)->find(elem);
            }
            return nullptr;
        }

        std::pair<std::shared_ptr<T>, bool> insert(const T& elem) {
//            if (l.size() != 0)
//                p2("meme", l.size());
            if (l.size() < max_node_elems) {
                auto ptr = std::make_shared<T>(elem);
                if (l.count(ptr)) {
                    return {l.find(ptr)->first, false};
                }
                l[ptr] = nullptr;
                return {ptr, true};
            }
            if (elem < *(l.begin()->first)) {
                if (first == nullptr) {
                    first = std::make_shared<BtreeNode>(max_node_elems);
                }
                return first->insert(elem);
            }
            auto it =  std::prev(l.upper_bound(std::make_shared<T>(elem)),1);
            if (*(it->first) == elem) {
                return {it->first, false};
            }

            if (l[it->first] == nullptr) {
                l[it->first] = std::make_shared<BtreeNode>(max_node_elems);

            }
            return l[it->first]->insert(elem);
        }

    };

    std::shared_ptr<T> next(std::shared_ptr<T> p) const {
        return p;
    }

    std::shared_ptr<BtreeNode> root;

};

template<typename T> btree<T>::btree(size_t maxNodeElems) {
    max_node_elems = maxNodeElems;

    root = std::make_shared<BtreeNode>(max_node_elems);

}

// todo
//template<typename T> btree<T>::btree(const btree<T>& original) = default;
//{
//
//}


//todo
//template<typename T> btree<T>::btree(btree<T>&& original) = default;
//{
//
//}
//template<typename T> btree<T>& btree<T>::operator=(const btree<T>& rhs){
////    btree<T> thing = btree<T>(rhs);
//    *this = btree<T>(rhs);
//    return *this;
//}
//template<typename T> btree<T>& btree<T>::operator=(btree<T>&& rhs) {
//    *this = btree<T>(std::move(rhs));
//    return *this;
//}


template<typename T> btree_iterator<T> btree<T>::find(const T& elem) {
    return typename btree_iterator<T>::btree_iterator( root->find(elem), root);
}
template<typename T> btree_iterator<T> btree<T>::find(const T& elem) const {
//    auto value =;

    return typename btree_iterator<T>::btree_iterator( root->find(elem), root);
}
template<typename T> std::pair<btree_iterator<T>, bool> btree<T>::insert(const T& elem) {
    auto p = root->insert(elem);
    return { typename btree_iterator<T>::btree_iterator(p.first, root), p.second};
}
template<typename T> btree<T>::~btree() {

}

//template<typename T> std::ostream& operator<< (std::ostream& os, const btree<T>& tree){
//    return os;
//}
#endif
