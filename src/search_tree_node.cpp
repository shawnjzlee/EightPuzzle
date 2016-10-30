#include <iostream>
#include <vector>

#include "search_tree_node.h"

SearchTreeNode::SearchTreeNode() { }

SearchTreeNode::SearchTreeNode(int _depth, int _path_cost, int _heuristic_value,
                               std::vector<int> _state) {
    depth = _depth;
    path_cost = _path_cost;
    heuristic_value = _heuristic_value;
    state = _state;
}

SearchTreeNode::~SearchTreeNode() { }