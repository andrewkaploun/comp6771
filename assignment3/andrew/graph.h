
#include<bits/stdc++.h>


namespace gdwg{




template<typename N, typename E> class Graph {

//typedef std::tuple<std::weak_ptr<N>, std::weak_ptr<N>, E> Edge;

private:
    struct SharedComparatorN {
        bool operator()(const std::shared_ptr<N>& lhs,
                        const std::shared_ptr<N>& rhs) const
        {
            return *lhs < *rhs;
        }
    };
    struct SharedComparatorES {
        bool operator()(const std::shared_ptr<E>& lhs,
                        const std::shared_ptr<E>& rhs) const
        {
            return *lhs < *rhs;
        }
    };

    class GraphNode {
    public:
        std::weak_ptr<N> val;
    };


    // polylogarithmic time for all operations; zero memory duplication.

    // the pair is for outgoing
    std::map<std::shared_ptr<GraphNode>,std::map<std::shared_ptr<GraphNode>,std::set<std::shared_ptr<E>,SharedComparatorES>>> outgoing;

    // for incoming:
    std::map<std::shared_ptr<GraphNode>,std::map<std::shared_ptr<GraphNode>,std::set<std::shared_ptr<E>,SharedComparatorES>>> incoming;

    std::map<std::shared_ptr<N>, std::shared_ptr<GraphNode>, SharedComparatorN> labelToNode;
    mutable typename std::map<std::shared_ptr<N>, std::shared_ptr<GraphNode>, SharedComparatorN>::const_iterator labelToNodeIterator;

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