
#include<bits/stdc++.h>


namespace gdwg{


// template<typename N, typename E> class GraphNode ;
// template<typename N, typename E> class Edge;

template<typename N, typename E> class Graph {
    // std::map<std::shared_ptr<N>, std::shared_ptr<GraphNode<N, E>>> nodes; 
    // std::set<std::shared_ptr<Edge<N,E>>> edges;

private:
    // std::map<std::shared_ptr<N>, std::map<std::weak_ptr<N>, std::unique_ptr<E>>> m; 
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
#include "graph.tem"




// template<typename N, typename E> class GraphNode {
// public:
//     std::shared_ptr<N> val;
//     std::set<std::weak_ptr<Edge<N, E>>> edges;
// };

// template<typename N, typename E> class Edge {
// public:
//     std::shared_ptr<E> weight;
//     std::weak_ptr<N> src;
//     std::weak_ptr<N> dst;
// };


};


// or instead, i could literally just have one private member in Graph and be done:
// std::map<std::shared_ptr<N>, std::map<std::weak_ptr<N>, std::unique_ptr<E>>> m; 