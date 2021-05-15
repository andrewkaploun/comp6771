
#include<bits/stdc++.h>


namespace gdwg{




template<typename N, typename E> class Graph {

typedef std::tuple<std::weak_ptr<N>, std::weak_ptr<N>, E> Edge;

private:
    struct SharedComparatorN {
        bool operator()(const std::shared_ptr<N>& lhs,
                        const std::shared_ptr<N>& rhs) const
        {
            return *lhs < *rhs;
        }
    };

    struct SharedComparatorNW {
        bool operator()(const std::weak_ptr<N>& lhs,
                        const std::weak_ptr<N>& rhs) const
        {
            return *lhs < *rhs;
        }
    };

    struct SharedComparatorE {
        bool operator()(const std::unique_ptr<E>& lhs,
                        const std::unique_ptr<E>& rhs) const
        {
            return std::get<2>(*lhs) < std::get<2>(*rhs);
        }
    };

    struct SharedComparatorES {
        bool operator()(const std::shared_ptr<E>& lhs,
                        const std::shared_ptr<E>& rhs) const
        {
            return *lhs < *rhs;
        }
    };


//    class  Edge {
//    public:
//        std::shared_ptr<E> weight;
//        std::weak_ptr<N> src;
//        std::weak_ptr<N> dst;
//    };
/*
 *
 * this is the good stuff i had before quitting:
    class GraphNode {
    public:
        std::weak_ptr<N> val;
        std::set<std::unique_ptr<Edge>, SharedComparatorE> edges; // stores outgoing edges
    };

    std::map<std::shared_ptr<N>, std::shared_ptr<GraphNode>, SharedComparatorN> nodes;



 */
//    std::set<std::shared_ptr<Edge>> edges;

//    std::map<std::shared_ptr<N>, std::pair<std::set<std::tuple< E,

    // polylogarithmic time for all operations; zero memory duplication.

    // the pair is for outgoing
    std::map<std::shared_ptr<N>, std::map<std::shared_ptr<N>, std::set<std::shared_ptr<E>,
        SharedComparatorES>, SharedComparatorN>, SharedComparatorN> outgoing;

    // for incoming:
    std::map<std::shared_ptr<N>, std::map<std::shared_ptr<N>, std::set<std::shared_ptr<E>,
        SharedComparatorES>, SharedComparatorN>, SharedComparatorN> incoming;

    N m;
public:
    Graph();

   // wait so are the constructors all just fine?

    bool addNode(const N& val);
    bool addEdge(const N& src, const N& dst, const E& w);
    bool replace(const N& oldData, const N& newData);
    void mergeReplace(const N& oldData, const N& newData);
    void deleteNode(const N&) noexcept;
    void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
    void clear() noexcept;
    bool isNode(const N& val) const;
    bool isConnected(const N& src, const N& dst) const;
    void printNodes() const;
    void printEdges(const N& val) const;

    void begin() const;
    bool end() const;
    void next() const;
    const N& value() const;
    void printAll() const;
};
#include "graph.tpp"





};


// or instead, i could literally just have one private member in Graph and be done:
// std::map<std::shared_ptr<N>, std::map<std::weak_ptr<N>, std::unique_ptr<E>>> m; 