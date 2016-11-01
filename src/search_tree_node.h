#ifndef SEARCH_TREE_NODE_H
#define SEARCH_TREE_NODE_H

#include <vector>

class SearchTreeNode {
    public:        
        struct node_status {
            int depth;              // depth in a tree
            int path_cost;          // g(n) - cost of path from start node to n
            int heuristic_value;    // h(n) - approx cost of cheapest path from n to goal
        }; node_status node_status;
    
        virtual std::vector<int> get_node_state() const = 0;
        virtual void node_expansion() = 0;
    
    protected:
};
#endif /* search_tree_node.h */
