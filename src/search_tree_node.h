#ifndef SEARCH_TREE_NODE_H
#define SEARCH_TREE_NODE_H

#include <vector>

class SearchTreeNode {
    public:
        virtual std::vector<int> get_node_state() = 0;
        
        virtual void node_expansion() = 0;
        
        struct node_status {
            int depth;              // depth in a tree
            int path_cost;          // g(n) - cost of path from start node to n
            int heuristic_value;    // h(n) - approx cost of cheapest path from n to goal
        }; node_status node_status;
    
    protected:
};
#endif /* search_tree_node.h */
