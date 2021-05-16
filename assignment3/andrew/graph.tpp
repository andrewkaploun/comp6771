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
        if (labelToNode.count(n) /*&&  *(it->first) == *n  */) {
            return false;
        }

        labelToNode[n] = std::make_shared<GraphNode>();
        labelToNode[n]->val = n;
        return true;
    }

    template<typename N, typename E> bool Graph<N, E>::addEdge(const N& src, const N& dst, const E& w) {
        std::shared_ptr<N> s = std::make_shared<N>(src);
        std::shared_ptr<N> d = std::make_shared<N>(dst);
        std::shared_ptr<E> e = std::make_shared<E>(w);
        if (!labelToNode.count(s) || !labelToNode.count(d)) {
            throw std::runtime_error("Deleting Edge of Non-existent Node");
        }
        std::shared_ptr<GraphNode> sNode = labelToNode[s];
        std::shared_ptr<GraphNode> dNode = labelToNode[d];

        if (outgoing[sNode][dNode].count(e)) {
            return false;
        }

        outgoing[sNode][dNode].insert(e);
        incoming[dNode][sNode].insert(e);

        return true;
    }
    template<typename N, typename E> bool Graph<N, E>::replace(const N& oldData, const N& newData) {
        auto oldVal = std::make_shared<N>(oldData);
        auto newVal = std::make_shared<N>(newData);
        if (!labelToNode.count(oldVal)) {
            throw std::runtime_error("Replacing Non-existent Node");
        }
        if (labelToNode.count(newVal)) {
            return false;
        }

        labelToNode[newVal] = labelToNode[oldVal];
        labelToNode[oldVal]->val = newVal;
        labelToNode.erase(oldVal);

        return true;
    }
    template<typename N, typename E> void Graph<N, E>::mergeReplace(const N& oldData, const N& newData) {
        auto oldVal = std::make_shared<N>(oldData);
        auto newVal = std::make_shared<N>(newData);
        if (!labelToNode.count(oldVal) || !labelToNode.count(newVal)) {
            throw std::runtime_error("Merge Replacing Non-existent Node");
        }
        // First, delete edges from old and add edges to new
        std::shared_ptr<GraphNode> oldNode = labelToNode[oldVal];
        std::shared_ptr<GraphNode> newNode = labelToNode[newVal];

        std::vector<std::pair<std::shared_ptr<GraphNode>, E>> oldOutgoing;

        for (auto p : outgoing[oldNode]) {
            for (auto pp : p.second) {
                oldOutgoing.push_back({p.first, *pp });
            }
        }

        for (auto edge : oldOutgoing) {
            auto otherNode = edge.first;
            auto e = edge.second;
                deleteEdge(*(oldNode->val.lock()), *(otherNode->val.lock()), e);
                addEdge(*(newNode->val.lock()), *(otherNode->val.lock()),e);
        }

        std::vector<std::pair<std::shared_ptr<GraphNode>, E>> oldIncoming;

        for (auto p : incoming[oldNode]) {
            for (auto pp : p.second) {
                oldIncoming.push_back({p.first, *pp });
            }
        }
        for (auto edge : oldIncoming) {
            auto otherNode = edge.first;
            auto e = edge.second;
                deleteEdge(*(otherNode->val.lock()), *(oldNode->val.lock()), e);
                addEdge(*(otherNode->val.lock()), *(newNode->val.lock()), e);
        }

        // Then, call deleteNode on old
        deleteNode(oldData);
    }

    template<typename N, typename E> void Graph<N, E>::deleteNode(const N& n) noexcept {
        auto val = std::make_shared<N>(n);
        if (labelToNode.count(val)) {
            auto node = labelToNode[val];

            std::vector<std::shared_ptr<GraphNode>> neighbors;
            // first delete all the edges, then delete the node manually
            for (auto e : outgoing[node]) {
                neighbors.push_back(e.first);
            }
            for (auto e : incoming[node]) {
                neighbors.push_back(e.first);
            }

            for (auto neighbor : neighbors) {
                outgoing[node][neighbor].clear();
                outgoing[neighbor][node].clear();
                incoming[node][neighbor].clear();
                incoming[neighbor][node].clear();
            }

            incoming.erase(node);
            outgoing.erase(node);
            labelToNode.erase(val);
        }
    }


    template<typename N, typename E> void Graph<N, E>::deleteEdge(const N& src, const N& dst, const E& w) noexcept {
        std::shared_ptr<N> s = std::make_shared<N>(src);
        std::shared_ptr<N> d = std::make_shared<N>(dst);

        if (!labelToNode.count(s) || !labelToNode.count(d)) {
            return;
        }

        auto src2 = labelToNode[s];
        auto dst2= labelToNode[d];

        std::shared_ptr<E> e = std::make_shared<E>(w);

        outgoing[src2][dst2].erase(e);
        incoming[dst2][src2].erase(e);
    }


    template<typename N, typename E> void Graph<N, E>::clear() noexcept {
        outgoing.clear();
        incoming.clear();
        labelToNode.clear();
    }

    template<typename N, typename E> bool Graph<N, E>::isNode(const N& val) const {
        auto v = std::make_shared<N>(val);
        return labelToNode.count(v) > 0 ? true : false;
    }

    template<typename N, typename E> bool Graph<N, E>::isConnected(const N& src, const N& dst) const {
        std::shared_ptr<N> s = std::make_shared<N>(src);
        std::shared_ptr<N> d = std::make_shared<N>(dst);

        if (!labelToNode.count(s) || !labelToNode.count(d)) {
            throw std::runtime_error("Checking if non-existent nodes are connected");
        }
        auto src2 = labelToNode.find(s)->second;
        auto dst2 = labelToNode.find(d)->second;
        auto it1 = outgoing.find(src2);
        if (it1 == outgoing.end()) return false;
        auto it2 = it1->second.find(dst2);
        if (it2 == it1->second.end()) return false;
        return !it2->second.empty();
//        return !outgoing[src2][dst2].empty();

    }
    template<typename N, typename E> void Graph<N, E>::printNodes() const {
        std::vector<std::pair<int, N>> degreeAndLabel;
        for (auto it : labelToNode) {
            int n = 0;
            auto it2 = outgoing.find(it.second);
            if (it2 != outgoing.end())
                for (auto bucket :it2->second) {
                    n+= bucket.second.size();
                }
            degreeAndLabel.push_back({n, *(it.first)});
        }
        std::sort(degreeAndLabel.begin(), degreeAndLabel.end());

        for (auto n : degreeAndLabel) {
            std::cout<< n.second<< std::endl;
        }
    }
    template<typename N, typename E> void Graph<N, E>::printEdges(const N& val) const {
        auto str = std::make_shared<N>(val);
        if (!labelToNode.count(str)) {
            throw std::runtime_error("Printing edges from fake node");
        }
        std::vector<std::pair<E, N>> v;
        std::cout<< "Edges attached to Node "<< val << std::endl;
        auto graphNode = labelToNode.find(str)->second;
        auto outgoingIt = outgoing.find(graphNode);
        if (outgoingIt != outgoing.end())
            for (auto p: outgoingIt->second) {
                for (auto e : p.second) {
                    v.push_back(std::make_pair(*e, *(p.first->val.lock())));
                }

            }
        if (!v.size()) {
            std::cout << "(null)"<<std::endl;
            return;
        }
        std::sort(v.begin(), v.end());
        for (auto p : v) {
            std::cout << p.second << " "<< p.first<< std::endl;
        }
    }

    template<typename N, typename E> void Graph<N, E>::begin() const {
        labelToNodeIterator = labelToNode.begin();
    }
    template<typename N, typename E> bool Graph<N, E>::end() const {
        return labelToNodeIterator == labelToNode.end();
    }
    template<typename N, typename E> void Graph<N, E>::next() const {
        ++labelToNodeIterator ;
    }
    template<typename N, typename E> const N& Graph<N, E>::value() const{
        return *(labelToNodeIterator->first);
        
    }

    template<typename N, typename E> void Graph<N, E>::printAll() const {
        std::cout <<"********** Print ALL ***********"<< std::endl;
        std::vector<std::pair<int, N>> degreeAndLabel;
        for (auto it : labelToNode) {
            int n = 0;
            auto it2 = outgoing.find(it.second);
            if (it2 != outgoing.end())
                for (auto bucket :it2->second) {
                    if (bucket.second.size()) {
                        n++;
                    }
                }
            degreeAndLabel.push_back({n, *(it.first)});
        }
        std::sort(degreeAndLabel.begin(), degreeAndLabel.end());

        for (auto n : degreeAndLabel) {
            printEdges(n.second);
        }

    }
