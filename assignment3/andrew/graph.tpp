/*

ok we plan it:
iterator and lookups of the edges are weak pointers i think?
then 

how clear works: oh we will just store a list of every node and delete le memes

also btw we'll have the invariant that nothing is null.

we'll probably have nodes and edges as types. within the actual graph itself we'll store 
weak pointers i think.

we'll have shared pointers in the map that holds shit in the graph.

we'll have an unordered set of the shared pointers of the edges i guess.

wait, how do we return const N& if we store our N's as shared pointers? can we 
return an rvalue reference? (like move a thing i hope?)
*/

// #include "graph.h"

// namespace fuck{


    // Graph::Graph<N, E>(void ) {

    // }
    template<typename N, typename E> Graph<N, E>::Graph(void) {

    }
    template<typename N, typename E> bool Graph<N, E>::addNode(const N& val) {
        std::shared_ptr<N> n = std::make_shared<N>(val);
        auto it = outgoing.find(n);
        if (it != outgoing.end() /*&&  *(it->first) == *n  */) {
            return false;
        }

        outgoing[n].clear();
        incoming[n].clear();
        return true;
    }

    template<typename N, typename E> bool Graph<N, E>::addEdge(const N& src, const N& dst, const E& w) {
        std::shared_ptr<N> s = std::make_shared<N>(src);
        std::shared_ptr<N> d = std::make_shared<N>(dst);
        std::shared_ptr<E> e = std::make_shared<E>(w);
        if (outgoing.find(s) == outgoing.end() || outgoing.find(d) == outgoing.end()) {
            throw std::runtime_error("Deleting Edge of Non-existent Node");
        }
        if (outgoing[s][d].count(e)) {
            return false;
        }

        outgoing[s][d].insert(e);
        incoming[d][s].insert(e);

        return true;
    }
    template<typename N, typename E> bool Graph<N, E>::replace(const N& oldData, const N& newData) {
        std::shared_ptr<N> old = std::make_shared<N>(src);
        if (outgoing)
    }
    template<typename N, typename E> void Graph<N, E>::mergeReplace(const N& oldData, const N& newData) {
    }
    template<typename N, typename E> void Graph<N, E>::deleteNode(const N&) noexcept {

    }
    template<typename N, typename E> void Graph<N, E>::deleteEdge(const N& src, const N& dst, const E& w) noexcept {

    }
    template<typename N, typename E> void Graph<N, E>::clear() noexcept {

    }
    template<typename N, typename E> bool Graph<N, E>::isNode(const N& val) const {
        return true;
    }
    template<typename N, typename E> bool Graph<N, E>::isConnected(const N& src, const N& dst) const {
        return true;
    }
    template<typename N, typename E> void Graph<N, E>::printNodes() const {

    }
    template<typename N, typename E> void Graph<N, E>::printEdges(const N& val) const {

    }

    template<typename N, typename E> void Graph<N, E>::begin() const {

    }
    template<typename N, typename E> bool Graph<N, E>::end() const {
        return true;
    }
    template<typename N, typename E> void Graph<N, E>::next() const {

    }
    template<typename N, typename E> const N& Graph<N, E>::value() const{
        // return *(m.begin()->first);
        return m;
        
    }

    template<typename N, typename E> void Graph<N, E>::printAll() const {

        
    }


// };