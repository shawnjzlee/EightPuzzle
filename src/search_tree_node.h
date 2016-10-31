#ifndef SEARCH_TREE_NODE_H
#define SEARCH_TREE_NODE_H

#include <vector>

class SearchTreeNode {
    public:
        SearchTreeNode();
        SearchTreeNode(int, int, int, std::vector<int>);
        ~SearchTreeNode();
    
        std::vector<int> get_node_state();
        void print_node_state();
        
        // int get_depth() const;
        // void set_depth(int);
        
        // int get_path_cost() const;
        // void set_path_cost(int);
        
        // int get_heuristic_value() const;
        // void set_heuristic_value(int);
        
        struct node_status {
            int depth;
            int path_cost;
            int heuristic_value;
        }; node_status node_status;
    
    private:
        std::vector<int> state; // grid values of this node
        
        int grid_width;
        // int depth;              // depth in a tree
        // int path_cost;          // g(n) - cost of path from start node to n
        // int heuristic_value;    // h(n) - approx cost of cheapest path from n to goal
};
#endif /* search_tree_node.h */
